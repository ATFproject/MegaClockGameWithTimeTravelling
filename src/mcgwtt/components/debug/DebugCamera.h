//
// Created by livefish on 5/23/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGCAMERA_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGCAMERA_H

#include "camera/CameraController.h"

namespace mcgwtt {
    class DebugCamera : public CameraController {
    public:
        void draw() override {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                json j(*this);
                std::cout << j.dump(2) << "\n";
            }
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
                rezoom(_zoom * 1.05);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
                rezoom(_zoom / 1.05);
        }

        void onNotify(const engine::Event &event) override {
            ENGINE_CHECK_EVENT(engine::game::GameResizeEvent,
                               resize(e->_newSize.x, e->_newSize.y);)
        }

        DebugCamera(mcgwtt::ViewController *controller, float i)
                : CameraController(controller, i) {}
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGCAMERA_H
