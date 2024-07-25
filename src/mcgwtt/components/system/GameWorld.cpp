// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 25.06.2024.
//

#include "GameWorld.h"

namespace mcgwtt {
    GameWorldPhysics::GameWorldPhysics(b2Vec2 gravity, float timestep, int velIters, int posIters)
            : _world(nullptr), _gravity(gravity), _timestep(timestep),
              _velIters(velIters), _posIters(posIters), _paused(false) {
    }

    void GameWorldPhysics::init(engine::game::Game &game) {
        game._world.emplace(_gravity);
        _world = &*game._world;

        ContactListenerAdder(*this);
        _world->SetContactListener(&_contactListener);
    }

    void GameWorldPhysics::onNotify(const engine::Event &event) {
        ENGINE_CHECK_EVENT(GamePausedEvent,
                           _paused = e->paused;
        )
    }

    void GameWorldPhysics::tick(engine::game::Game &game) {
        if (!_paused)
            _world->Step(_timestep, _velIters, _posIters);
    }
}
