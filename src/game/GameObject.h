//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H

#include "components/EmptyComponents.h"

namespace game {
    class GameObject {
    public:
        GameObject() {
            _input = &emptyInputComponent;
            _physics = &emptyPhysicsComponent;
            _graphics = &emptyGraphicsComponent;
        }

        void setInput(components::InputComponent *input = nullptr) {
            _input = (input)? input : &emptyInputComponent;
        }

        void setGraphics(components::GraphicsComponent *graphics = nullptr) {
            _graphics = (graphics)? graphics : &emptyGraphicsComponent;
        }

        void setPhysics(components::PhysicsComponent *physics = nullptr) {
            _physics = (physics)? physics : &emptyPhysicsComponent;
        }

        void tick(sf::Time dt, Game &game) {
            _input->tick(this, game);
            _physics->tick(this, dt, game);
        }

        void draw() {
            _graphics->draw(this);
        }

    private:
        components::InputComponent *_input;
        components::PhysicsComponent *_physics;
        components::GraphicsComponent *_graphics;
        static components::EmptyInputComponent emptyInputComponent;
        static components::EmptyGraphicsComponent emptyGraphicsComponent;
        static components::EmptyPhysicsComponent emptyPhysicsComponent;
    };
} // game

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H
