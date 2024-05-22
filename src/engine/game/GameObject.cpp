// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "GameObject.h"
#include "components/EmptyComponents.h"
#include "ViewController.h"

namespace engine::game {
    void GameObject::init(Game &game) {
        _input->init(game);
        _physics->init(game);
        _graphics->init(game);
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

    void GameObject::onNotify(const Event &event) {
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