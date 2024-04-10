//
// Created by livefish on 4/5/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H

#include "components/ComponentInterface.h"
#include "game/Game.h"


namespace mcgwtt {
    class CameraController : public engine::components::GraphicsComponent {
    private:
        sf::RenderWindow *_win;
        sf::View _view;
        float _zoom;
        sf::Text _stats;

        void resize(float newW, float newH) {
            _view.setCenter(0, 0);
            _view.setSize(newW / _zoom, newH / _zoom);

            _win->setView(_view);
        }

    public:
        CameraController(sf::RenderWindow *win, float initialZoom)
                : _win(win), _view(win->getDefaultView()), _zoom(initialZoom) {
            _stats.setFont(engine::resourceHandler.addRes(new engine::Font("arialmt.ttf"))->getFont());
            _stats.setString("STATS HERE");
            _stats.setStyle(sf::Text::Bold | sf::Text::Underlined);
            _stats.setCharacterSize(24);
        }

        void draw(engine::game::GameObject *gameObject) override {
            sf::View view = _win->getView();
            _win->setView(_win->getDefaultView());
            _stats.setString("No stats here(((");
            _win->draw(_stats);
            _win->setView(view);
        }

        void onNotify(const engine::events::Event &event) override {
            ENGINE_CHECK_EVENT(engine::game::GameResizeEvent, resize(e->_newSize.x, e->_newSize.y);)
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H
