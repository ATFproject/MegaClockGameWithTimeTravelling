//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H

#include "components/Components.h"
#include "SFML/System/Clock.hpp"

namespace game {
    class GameObject {
    public:
        GameObject() = delete;

        GameObject(InputComponent *input, PhysicsComponent *physics, GraphicsComponent *graphics) :
                _input(input), _physics(physics), _graphics(graphics) {}

        void tick(sf::Time dt, Game &game) {
            _input->tick(this);
            _physics->tick(this, dt, game);
        }

        void draw() {
            _graphics->draw(this);
        }

    private:
        InputComponent *_input;
        PhysicsComponent *_physics;
        GraphicsComponent *_graphics;
    };
} // game

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H
