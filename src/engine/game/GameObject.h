//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H

#include "GameDef.h"
#include "components/ComponentDef.h"
#include "observers/Observer.h"
#include "observers/Subject.h"

namespace engine::game {
    class GameObject : public Observer, public Subject {
    public:
        GameObject();
        GameObject(components::InputComponent *ic, components::PhysicsComponent *pc, components::GraphicsComponent *gc);

        void tick(sf::Time dt, Game &game);
        void draw();
        void onNotify(events::Type type) override;
        void onNotify(events::Event *event) override;

    private:
        components::InputComponent *_input;
        components::PhysicsComponent *_physics;
        components::GraphicsComponent *_graphics;

        static components::EmptyInputComponent emptyInputComponent;
        static components::EmptyGraphicsComponent emptyGraphicsComponent;
        static components::EmptyPhysicsComponent emptyPhysicsComponent;
    };
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H
