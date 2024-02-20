//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEOBJECT_H

#include "GameDef.h"
#include "components/ComponentDef.h"

namespace engine::game {
    class GameObject {
    public:
        GameObject();

        void setInput(components::InputComponent *input = nullptr);
        void setGraphics(components::GraphicsComponent *graphics = nullptr);
        void setPhysics(components::PhysicsComponent *physics = nullptr);

        void tick(sf::Time dt, Game &game);
        void draw();

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
