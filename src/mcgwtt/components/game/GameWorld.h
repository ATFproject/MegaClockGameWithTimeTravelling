//
// Created by livefish on 3/25/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWORLD_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWORLD_H

#include "components/ComponentInterface.h"

namespace mcgwtt::components::game {
    struct GamePausedEvent : public engine::events::Event {
        bool _paused;
        explicit GamePausedEvent(bool paused) : _paused(paused) {}
    };

    class GameWorldPhysics : public engine::components::PhysicsComponent {
    private:
        b2World _world;
        float _timestep;
        int _velIters, _posIters;
        bool _paused;

    public:
        GameWorldPhysics(window::GameWindow &win, b2Vec2 gravity, float timestep, int velIters, int posIters)
                : _world(gravity), _timestep(timestep), _velIters(velIters), _posIters(posIters), _paused(false) {
            win.addWorld(&_world);
        }

        void onNotify(const engine::events::Event &event) override {
            ENGINE_CHECK_EVENT(GamePausedEvent,
                               _paused = e->_paused;
            )
        }

        void tick(engine::game::GameObject *gameObject, engine::game::Game &game) override {
            if (!_paused)
                _world.Step(_timestep, _velIters, _posIters);
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWORLD_H
