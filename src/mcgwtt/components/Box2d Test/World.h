//
// Created by livefish on 3/9/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_WORLD_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_WORLD_H

#include "components/ComponentInterface.h"
#include "GameWindow.h"

namespace mcgwtt::components {
    class WorldPhysics : public engine::components::PhysicsComponent {
    private:
        b2World _world;
        float _timestep;
        int _velIters, _posIters;

    public:
        WorldPhysics(window::GameWindow &win, b2Vec2 gravity, float timestep, int velIters, int posIters)
                : _world(gravity), _timestep(timestep), _velIters(velIters), _posIters(posIters) {
            win.addWorld(&_world);
        }

        void tick(engine::game::GameObject *gameObject, engine::game::Game &game) override {
            _world.Step(_timestep, _velIters, _posIters);
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_WORLD_H
