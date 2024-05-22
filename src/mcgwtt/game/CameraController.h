//
// Created by livefish on 4/5/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H

#include "components/ComponentInterface.h"
#include "game/Game.h"


namespace mcgwtt {
    class CameraController : public AbleToControlViewComponent {
    private:
        sf::View _view;
        float _zoom;
        float _saveW{}, _saveH{};

        void rezoom(float newZoom) {
            _zoom = newZoom;
            resize(_saveW, _saveH, _view.getCenter().x, _view.getCenter().y);
            std::cout << "New zoom: " << newZoom << "'\n";
        }

        void resize(float newW, float newH, float x = 0, float y = 0) {
            _saveW = newW;
            _saveH = newH;
            _view.setCenter(x, y);
            _view.setSize(newW / _zoom, newH / _zoom);
            notify(SetViewEvent(_view));
        }

    public:
        CameraController(ViewController *viewController, float initialZoom)
                : AbleToControlViewComponent(viewController), _zoom(initialZoom) {
        }

        void draw() override {
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
            ENGINE_CHECK_EVENT(engine::game::GameResizeEvent, resize(e->_newSize.x, e->_newSize.y);)
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H
