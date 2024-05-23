//
// Created by livefish on 4/10/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGGRID_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGGRID_H

#include "components/ComponentInterface.h"
#include "camera/ViewController.h"

namespace mcgwtt {
    class DebugGridGraphics : public AbleToControlViewComponent {
    private:
        sf::RectangleShape _xAxis, _yAxis;
        std::vector<sf::RectangleShape> _points;
        sf::RenderWindow *_win;
        const float _lineWidth = 1;

        void resizeAxis(sf::Vector2u newSize) {
            _xAxis.setSize(sf::Vector2f(newSize.x, _lineWidth));
            _xAxis.setPosition(0, newSize.y / 2.0 - _lineWidth / 2);
            _xAxis.setFillColor(sf::Color::Blue);

            _yAxis.setSize(sf::Vector2f(_lineWidth, newSize.y));
            _yAxis.setPosition(newSize.x / 2.0 - _lineWidth / 2, 0);
            _yAxis.setFillColor(sf::Color::Red);

            float zoom = newSize.x / _win->getView().getSize().x;
            _points.clear();
            for (uint i = 0; i < newSize.x; i += zoom) {
                sf::RectangleShape shape(sf::Vector2f(_lineWidth, newSize.y));
                shape.setPosition(i - _lineWidth / 2.f, 0);
                shape.setFillColor(sf::Color::Black);
                _points.push_back(shape);
            }

            for (uint i = 0; i < newSize.y; i += zoom) {
                sf::RectangleShape shape(sf::Vector2f(newSize.x, _lineWidth));
                shape.setPosition(0, i - _lineWidth / 2.f);
                shape.setFillColor(sf::Color::Black);
                _points.push_back(shape);
            }
        }

    public:
        DebugGridGraphics(sf::RenderWindow *win, ViewController *viewController)
                : AbleToControlViewComponent(viewController), _win(win) {}

        void init(engine::game::Game &game) override {
            game.addObserver(this);
        }

        void onNotify(const engine::Event &event) override {
            ENGINE_CHECK_EVENT(engine::game::GameResizeEvent, resizeAxis(e->_newSize);)
        }

        void draw() override {
            notify(PushViewEvent());
            notify(SetFullScreenViewEvent());

            for (auto &p : _points)
                _win->draw(p);

            _win->draw(_xAxis);
            _win->draw(_yAxis);

            notify(PopViewEvent());
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGGRID_H
