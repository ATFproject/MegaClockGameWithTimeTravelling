//
// Created by livefish on 2/19/24.
//

#include "GameObject.h"
#include "components/EmptyComponents.h"

namespace engine::game {
    void GameObject::init(Game &game) {
        _input->init(this, game);
        _physics->init(this, game);
        _graphics->init(this, game);
    }

    void GameObject::tick(Game &game) {
        _input->tick(game);
        _physics->tick(game);
    }

    void GameObject::draw() {
        _graphics->draw();
    }

    GameObject::GameObject(components::InputComponent *input, components::PhysicsComponent *physics,
                           components::GraphicsComponent *graphics) {
        if (input) {
            _input = input;
            _input->addObserver(this);
            addObserver(_input);
        }
        if (physics) {
            _physics = physics;
            _physics->addObserver(this);
            addObserver(_physics);
        }
        if (graphics) {
            _graphics = graphics;
            _graphics->addObserver(this);
            addObserver(_graphics);
        }
    }

    void GameObject::onNotify(const events::Event &event) {
        notify(event);
    }

    GameObject::~GameObject() {
        if (_input != &_emptyInputComponent)
            delete _input;
        if (_physics != &_emptyPhysicsComponent)
            delete _physics;
        if (_graphics != &_emptyGraphicsComponent)
            delete _graphics;
    }
}