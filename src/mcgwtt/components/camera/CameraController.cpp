// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 25.06.2024.
//

#include "CameraController.h"

namespace mcgwtt {
    CameraController::CameraController(ViewController *viewController, float initialZoom)
            : AbleToControlViewComponent(viewController), _zoom(initialZoom) {
    }

    CameraController::CameraController(const CameraController &old, ViewController *viewController)
            : AbleToControlViewComponent(viewController),
              _view(old._view), _zoom(old._zoom), _saveW(old._saveW), _saveH(old._saveH) {
    }

    void CameraController::rezoom(float newZoom) {
        _zoom = newZoom;
        resize(_saveW, _saveH, _view.getCenter().x, _view.getCenter().y);
    }

    void CameraController::resize(float newW, float newH, float x, float y) {
        _saveW = newW;
        _saveH = newH;
        _view.setCenter(x, y);
        _view.setSize(newW / _zoom, newH / _zoom);
        notify(SetViewEvent(_view));
    }

    void CameraController::onNotify(const engine::Event &event) {
        ENGINE_CHECK_EVENT(engine::game::GameResizeEvent,
                           resize(static_cast<float>(e->_newSize.x), static_cast<float>(e->_newSize.y),
                                  _view.getCenter().x, _view.getCenter().y);)
    }

    void CameraController::draw() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            json j(*this);
            std::cout << j.dump(2) << "\n";
        }
    }


    void to_json(json &j, const CameraController &camera) {
        j["zoom"] = camera._zoom;
        j["saved width"] = camera._saveW;
        j["saved height"] = camera._saveH;
        auto &view = camera._view;
        j["view"] = {
                {"size",     {{"width", view.getSize().x},        {"height", view.getSize().y}}},
                {"center",   {{"x",     view.getCenter().x},      {"y",      view.getCenter().y}}},
                {"rotation", view.getRotation()},
                {"viewport", {
                              {"left",  view.getViewport().left}, {"top",    view.getViewport().top},
                                     {"width", view.getViewport().width}, {"height", view.getViewport().height}
                             }}
        };
    }
    void from_json(const json &j, CameraController &camera) {
        j.at("zoom").get_to(camera._zoom);
        j.at("saved width").get_to(camera._saveW);
        j.at("saved height").get_to(camera._saveH);
        auto size = j["view"]["size"];
        camera._view.setSize(size["width"], size["height"]);
        auto center = j["view"]["center"];
        camera._view.setCenter(center["x"], center["y"]);
        camera._view.setRotation(j["view"]["rotation"]);
        auto viewport = j["view"]["viewport"];
        camera._view.setViewport(sf::FloatRect(
                viewport["left"], viewport["top"], viewport["width"], viewport["height"]
        ));
    }


}
