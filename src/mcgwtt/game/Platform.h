// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 4/10/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_PLATFORM_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_PLATFORM_H

#include "BasicBody.h"

namespace mcgwtt {
    class Platform : public BasicBody {
    public:
        Platform(sf::RenderWindow *win, GameWorldPhysics *worldPh, float x, float y, float w, float h)
                : BasicBody(win, worldPh, _physicsInit, _physicsTick, _physicsOnNotify, _initSprites),
                  _x(x), _y(y), _w(w), _h(h) {}
    private:
        float _x, _y, _w, _h;

        physicsInitFunction _physicsInit = [this](engine::game::Game &game) -> bodyFixVecPair {
            b2BodyDef bd;
            bd.type = b2_kinematicBody;
            bd.position.Set(_x, _y);
            bd.gravityScale = 0;
            bd.fixedRotation = true;

            MCGWTT_BASIC_BODY_CREATE_BODY(bd)

            b2PolygonShape shape;
            shape.SetAsBox(_w, _h, b2Vec2(_x, _y), 0);
            MCGWTT_BASIC_BODY_CREATE_FIXTURE(shape, 5.0f)

            return res;
        };

        physicsTickFunction _physicsTick = [](engine::game::Game &game) {};
        onNotifyFunction _physicsOnNotify = [](const engine::Event &event) {};

        initSpritesFunction _initSprites = [this](const BasicBodyData *data) -> bodyAnimPair {
            return bindAnimations(data, Animation::getStaticAnimation("ground/ground tile.png"));
        };
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_PLATFORM_H
