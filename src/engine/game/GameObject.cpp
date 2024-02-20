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

    void GameObject::setInput(components::InputComponent *input) {
        _input = (input)? input : &emptyInputComponent;
    }

    void GameObject::setGraphics(components::GraphicsComponent *graphics) {
        _graphics = (graphics)? graphics : &emptyGraphicsComponent;
    }

    void GameObject::setPhysics(components::PhysicsComponent *physics) {
        _physics = (physics)? physics : &emptyPhysicsComponent;
    }

    void GameObject::tick(sf::Time dt, Game &game) {
        _input->tick(this, game);
        _physics->tick(this, dt, game);
    }

    void GameObject::draw() {
        _graphics->draw(this);
    }
}