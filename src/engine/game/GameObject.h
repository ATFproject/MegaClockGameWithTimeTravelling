// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H

#include "GameDef.h"
#include "components/EmptyComponents.h"
#include "observers/Subject.h"

namespace engine::game {
    class GameObject : public Observer, public Subject {
    public:
        GameObject() = default;
        GameObject(components::InputComponent *ic, components::PhysicsComponent *pc, components::GraphicsComponent *gc);
        ~GameObject() override;

        void init(Game &game);
        void tick(Game &game);
        void draw();
        void onNotify(const Event &event) override;

    private:
        components::InputComponent *_input = &_emptyInputComponent;
        components::PhysicsComponent *_physics = &_emptyPhysicsComponent;
        components::GraphicsComponent *_graphics = &_emptyGraphicsComponent;

        static inline components::EmptyInputComponent _emptyInputComponent;
        static inline components::EmptyGraphicsComponent _emptyGraphicsComponent;
        static inline components::EmptyPhysicsComponent _emptyPhysicsComponent;
    };
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H
