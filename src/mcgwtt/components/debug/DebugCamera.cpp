// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 25.06.2024.
//

#include "DebugCamera.h"

namespace mcgwtt {
    DebugCamera::DebugCamera(mcgwtt::ViewController *controller, float i)
            : CameraController(controller, i) {}

    void DebugCamera::onNotify(const engine::Event &event) {
        ENGINE_CHECK_EVENT(engine::game::GameResizeEvent,
                           resize(static_cast<float>(e->_newSize.x), static_cast<float>(e->_newSize.y));)
    }

    void DebugCamera::draw() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            _view.move({0, -0.1f});
            rezoom(_zoom);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            _view.move({0, 0.1f});
            rezoom(_zoom);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _view.move({-0.1f, 0});
            rezoom(_zoom);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _view.move({0.1f, 0});
            rezoom(_zoom);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
            rezoom(_zoom * 1.05f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
            rezoom(_zoom / 1.05f);
    }
}
