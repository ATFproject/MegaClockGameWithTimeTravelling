// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 25.06.2024.
//

#include "DebugGrid.h"

namespace mcgwtt {
    DebugGridGraphics::DebugGridGraphics(sf::RenderTarget *target, ViewController *viewController)
            : AbleToControlViewComponent(viewController), _target(target) {}

    void DebugGridGraphics::init(engine::game::Game &game) {
        game.addObserver(this);
    }
    void DebugGridGraphics::onNotify(const engine::Event &event) {
        ENGINE_CHECK_EVENT(engine::game::GameResizeEvent, resizeAxis(sf::Vector2f(e->newSize));)
    }
    void DebugGridGraphics::draw() {
        notify(PushViewEvent());
        notify(SetFullScreenViewEvent());

        for (auto &p : _points)
            _target->draw(p);

        _target->draw(_xAxis);
        _target->draw(_yAxis);

        notify(PopViewEvent());
    }

    void DebugGridGraphics::resizeAxis(sf::Vector2f newSize) {
        _xAxis.setSize(sf::Vector2f(newSize.x, _lineWidth));
        _xAxis.setPosition(0, newSize.y / 2.0f - _lineWidth / 2);
        _xAxis.setFillColor(sf::Color::Blue);

        _yAxis.setSize(sf::Vector2f(_lineWidth, newSize.y));
        _yAxis.setPosition(newSize.x / 2.0f - _lineWidth / 2, 0);
        _yAxis.setFillColor(sf::Color::Red);

        float zoom = newSize.x / _target->getView().getSize().x;
        _points.clear();
        for (float i = 0; i < newSize.x; i += zoom) {
            sf::RectangleShape shape(sf::Vector2f(_lineWidth, newSize.y));
            shape.setPosition(i - _lineWidth / 2.f, 0);
            shape.setFillColor(sf::Color::Black);
            _points.push_back(shape);
        }

        for (float i = 0; i < newSize.y; i += zoom) {
            sf::RectangleShape shape(sf::Vector2f(newSize.x, _lineWidth));
            shape.setPosition(0, i - _lineWidth / 2.f);
            shape.setFillColor(sf::Color::Black);
            _points.push_back(shape);
        }
    }

}
