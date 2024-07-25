// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 3/25/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWORLD_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWORLD_H

#include "components/ComponentInterface.h"
#include "mcgwtt/game/ContactListener/ContactListenerAdder.h"

namespace mcgwtt {
    struct GamePausedEvent : public engine::Event {
        bool _paused;
        explicit GamePausedEvent(bool paused) : _paused(paused) {}
    };

    class GameWorldPhysics : public engine::components::PhysicsComponent {
    public:
        GameWorldPhysics(b2Vec2 gravity, float timestep, int velIters, int posIters);

        void init(engine::game::Game &game) override;
        void onNotify(const engine::Event &event) override;
        void tick(engine::game::Game &game) override;

    public:
        ContactListener _contactListener;

    private:
        b2World *_world;
        b2Vec2 _gravity;
        float _timestep;
        int _velIters, _posIters;
        bool _paused;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWORLD_H
