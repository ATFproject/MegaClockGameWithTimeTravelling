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
        void onNotify(const events::Event &event) override;

    private:
        components::InputComponent *_input = &emptyInputComponent;
        components::PhysicsComponent *_physics = &emptyPhysicsComponent;
        components::GraphicsComponent *_graphics = &emptyGraphicsComponent;

        static inline components::EmptyInputComponent emptyInputComponent;
        static inline components::EmptyGraphicsComponent emptyGraphicsComponent;
        static inline components::EmptyPhysicsComponent emptyPhysicsComponent;
    };
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H
