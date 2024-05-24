//
// Created by livefish on 4/5/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H

#include "ViewController.h"

namespace mcgwtt {
    class CameraController : public AbleToControlViewComponent {
    protected:
        sf::View _view;
        float _zoom;
        float _saveW{}, _saveH{};

        void rezoom(float newZoom) {
            _zoom = newZoom;
            resize(_saveW, _saveH, _view.getCenter().x, _view.getCenter().y);
        }

        void resize(float newW, float newH, float x = 0, float y = 0) {
            _saveW = newW;
            _saveH = newH;
            _view.setCenter(x, y);
            _view.setSize(newW / _zoom, newH / _zoom);
            notify(SetViewEvent(_view));
        }

        friend void to_json(nlohmann::json &j, const CameraController &camera) {
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

        friend void from_json(const json &j, CameraController &camera) {
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

    public:
        CameraController(ViewController *viewController, float initialZoom)
                : AbleToControlViewComponent(viewController), _zoom(initialZoom) {
        }

        CameraController(const CameraController &old, ViewController *viewController)
                : AbleToControlViewComponent(viewController),
                  _view(old._view), _zoom(old._zoom), _saveW(old._saveW), _saveH(old._saveH) {
        }

        void onNotify(const engine::Event &event) override {
            ENGINE_CHECK_EVENT(engine::game::GameResizeEvent,
                               resize(e->_newSize.x, e->_newSize.y, _view.getCenter().x, _view.getCenter().y);)
        }

        void draw() override {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                json j(*this);
                std::cout << j.dump(2) << "\n";
            }
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H
