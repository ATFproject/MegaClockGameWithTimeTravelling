//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H

#include "SFML/Graphics.hpp"
#include "components/Components.h"

#include "Game.h"

namespace game {
    class GameObject {
    public:
        GameObject() = delete;

        GameObject(InputComponent *input, PhysicsComponent *physics, GraphicsComponent *graphics) :
                _input(input), _physics(physics), _graphics(graphics) {}

        void tick(double dt, Game &game) {
            _input->tick(this);
            _physics->tick(this, dt, game);
        }

        void draw(const Game &game) {
            _graphics->draw(this, game);
        }

    private:
        InputComponent *_input;
        PhysicsComponent *_physics;
        GraphicsComponent *_graphics;
    };
} // game

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H
