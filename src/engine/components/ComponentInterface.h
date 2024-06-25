// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_COMPONENTINTERFACE_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_COMPONENTINTERFACE_H

#include "observers/Subject.h"
#include "game/Game.h"

namespace engine::components {
    class InputComponent : public Observer, public Subject {
    public:
        virtual void init(engine::game::Game &game) {}
        virtual void tick(engine::game::Game &game) = 0;
        ~InputComponent() override = default;
    };

    class PhysicsComponent : public Observer, public Subject {
    public:
        virtual void init(engine::game::Game &game) {}
        virtual void tick(engine::game::Game &game) = 0;
        ~PhysicsComponent() override = default;
    };

    class GraphicsComponent : public Observer, public Subject {
    public:
        virtual void init(engine::game::Game &game) {}
        virtual void draw() = 0;
        ~GraphicsComponent() override = default;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_COMPONENTINTERFACE_H
