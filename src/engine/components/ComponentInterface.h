//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_COMPONENTINTERFACE_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_COMPONENTINTERFACE_H

#include "ComponentDef.h"
#include "observers/Subject.h"
#include "game/GameDef.h"

namespace engine::components {
    class GraphicsComponent : public Observer, public Subject {
    public:
        virtual void init(game::GameObject *gameObject, game::Game &game) {}

        virtual void preDraw(game::GameObject *gameObject) {}
        virtual void postDraw(game::GameObject *gameObject) {}
        virtual void draw(game::GameObject *gameObject) = 0;
        ~GraphicsComponent() override = default;
    };

    class InputComponent : public Observer, public Subject {
    public:
        virtual void init(game::GameObject *gameObject, game::Game &game) {}

        virtual void tick(game::GameObject *gameObject, game::Game &game) = 0;
        ~InputComponent() override = default;
    };

    class PhysicsComponent : public Observer, public Subject {
    public:
        virtual void init(game::GameObject *gameObject, game::Game &game) {}

        virtual void tick(game::GameObject *gameObject, game::Game &game) = 0;
        ~PhysicsComponent() override = default;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_COMPONENTINTERFACE_H
