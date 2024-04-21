//
// Created by livefish on 4/21/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_VIEWCONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_VIEWCONTROLLER_H

#include "components/ComponentInterface.h"
#include "game/Game.h"

namespace mcgwtt {
    struct PushViewEvent : engine::Event {
    };
    struct PopViewEvent : engine::Event {
    };
    struct SetFullScreenViewEvent : engine::Event {
    };
    struct SetViewEvent : engine::Event {
        sf::View _view;
        explicit SetViewEvent(const sf::View &view) : _view(view) {}
    };

    class ViewController : public engine::components::GraphicsComponent {
    private:
        sf::Vector2u _size;
        sf::View _view;
        std::stack<sf::View> _views;

        void pushView() {
            _views.push(_view);
        }

        void popView() {
            _view = _views.top();
            _views.pop();
            notify(window::WindowViewChangedEvent(_view));
        }

        void setView(const sf::View &view) {
            _view = view;
            notify(window::WindowViewChangedEvent(_view));
        }

        void setFullScreenView() {
            setView(getFullScreenView());
        }

        sf::View getFullScreenView() const {
            sf::View view(sf::Vector2f(_size.x / 2.f, _size.y / 2.f),
                          sf::Vector2f(_size.x, _size.y));
            return view;
        }

    public:
        void onNotify(const engine::Event &event) override {
            ENGINE_CHECK_EVENT(engine::game::GameResizeEvent, _size = e->_newSize;)
            ENGINE_CHECK_EVENT(PushViewEvent, pushView();)
            ENGINE_CHECK_EVENT(PopViewEvent, popView();)
            ENGINE_CHECK_EVENT(SetViewEvent, setView(e->_view);)
            ENGINE_CHECK_EVENT(SetFullScreenViewEvent, setFullScreenView();)
        }

        void draw() override {
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_VIEWCONTROLLER_H
