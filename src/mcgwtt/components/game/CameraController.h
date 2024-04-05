//
// Created by livefish on 4/5/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H

#include "components/ComponentInterface.h"
#include "game/Game.h"

namespace mcgwtt::components::game {
    class CameraController : public engine::components::GraphicsComponent {
    private:
        sf::RenderWindow *_win;
        sf::View _view;
        float _zoom;

    public:
        CameraController(sf::RenderWindow *win, float initialZoom)
                : _win(win), _view(win->getDefaultView()), _zoom(initialZoom) {
        }

        void init(engine::game::GameObject *gameObject, engine::game::Game &game) override {
            GraphicsComponent::init(gameObject, game);
        }

        void draw(engine::game::GameObject *gameObject) override {}

        void onNotify(const engine::events::Event &event) override {
            ENGINE_CHECK_EVENT(engine::game::GameResizeEvent,
                               _view.setCenter(0, 0);
                                       _view.setSize(_win->getDefaultView().getSize() / _zoom);
                                       _win->setView(_view);
            )
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H
