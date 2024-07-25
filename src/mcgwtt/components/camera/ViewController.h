// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 4/21/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_VIEWCONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_VIEWCONTROLLER_H

#include "Events.h"
#include "components/ComponentInterface.h"

namespace mcgwtt {
    struct PushViewEvent : engine::Event {
    };
    struct PopViewEvent : engine::Event {
    };
    struct SetFullScreenViewEvent : engine::Event {
    };

    struct SetViewEvent : engine::Event {
        sf::View view;
        explicit SetViewEvent(const sf::View &view) : view(view) {}
    };

    class ViewController : public engine::components::GraphicsComponent {
    public:
        void onNotify(const engine::Event &event) override;
        void init(engine::game::Game &game) override;
        void draw() override;

    private:
        void pushView();
        void popView();

        void setView(const sf::View &view);
        void setFullScreenView();

        sf::View getFullScreenView() const;

    private:
        sf::Vector2u _size;
        sf::View _view;
        std::stack<sf::View> _views;
    };

    class AbleToControlViewComponent : public engine::components::GraphicsComponent {
    public:
        AbleToControlViewComponent() = delete;
        explicit AbleToControlViewComponent(ViewController *viewController);

        void setViewController(ViewController *viewController);
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_VIEWCONTROLLER_H
