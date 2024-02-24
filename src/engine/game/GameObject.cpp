//
// Created by livefish on 2/19/24.
//

#include "GameObject.h"
#include "components/EmptyComponents.h"

namespace engine::game {
    components::EmptyInputComponent GameObject::emptyInputComponent;
    components::EmptyGraphicsComponent GameObject::emptyGraphicsComponent;
    components::EmptyPhysicsComponent GameObject::emptyPhysicsComponent;

    GameObject::GameObject() {
        _input = &emptyInputComponent;
        _physics = &emptyPhysicsComponent;
        _graphics = &emptyGraphicsComponent;
    }

    void GameObject::tick(sf::Time dt, Game &game) {
        _input->tick(this, game);
        _physics->tick(this, dt, game);
    }

    void GameObject::draw() {
        _graphics->draw(this);
    }

    GameObject::GameObject(components::InputComponent *input, components::PhysicsComponent *physics,
                           components::GraphicsComponent *graphics) {
        _input = (input)? input : &emptyInputComponent;
        _physics = (physics)? physics : &emptyPhysicsComponent;
        _graphics = (graphics)? graphics : &emptyGraphicsComponent;
    }
}