//
// Created by livefish on 4/10/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGGRID_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGGRID_H

#include "components/ComponentInterface.h"

namespace mcgwtt {
    class DebugGridGraphics : public engine::components::GraphicsComponent {
    private:
        sf::RectangleShape _xAxis{}, _yAxis{};
        sf::RenderWindow *_win;

        void resizeAxis(sf::Vector2u newSize) {
            _xAxis.setSize(sf::Vector2f(newSize.x, 5));
            _xAxis.setPosition(0, newSize.y / 2 - 2.5);
            _xAxis.setFillColor(sf::Color::Blue);

            _yAxis.setSize(sf::Vector2f(5, newSize.y));
            _yAxis.setPosition(newSize.x / 2 - 2.5, 0);
            _yAxis.setFillColor(sf::Color::Red);
        }

    public:
        explicit DebugGridGraphics(sf::RenderWindow *win) : _win(win) {}

        void init(engine::game::GameObject *gameObject, engine::game::Game &game) override {
            game.addObserver(this);
        }

        void onNotify(const engine::events::Event &event) override {
            ENGINE_CHECK_EVENT(engine::game::GameResizeEvent, resizeAxis(e->_newSize);)
        }

        void draw() override {
            auto viewBackup = _win->getView();
            _win->setView(_win->getDefaultView());
            _win->draw(_xAxis);
            _win->draw(_yAxis);
            _win->setView(viewBackup);
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGGRID_H
