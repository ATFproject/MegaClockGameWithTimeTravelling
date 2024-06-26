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

        BasicBody::physicsInitFunction _physicsInit = [this](engine::game::Game &game) -> std::vector<b2Body *> {
            b2BodyDef bd;
            bd.type = b2_kinematicBody;
            bd.position.Set(_x, _y);
            bd.gravityScale = 0;
            bd.fixedRotation = true;
            std::vector<b2Body *> bodies;
            bodies.push_back(game._world->CreateBody(&bd));

            b2PolygonShape shape;
            shape.SetAsBox(_w, _h, b2Vec2(_x, _y), 0);
            bodies[0]->CreateFixture(&shape, 5.0f);

            return bodies;
        };

        BasicBody::physicsTickFunction _physicsTick = [](engine::game::Game &game) {};
        BasicBody::onNotifyFunction _physicsOnNotify = [](const engine::Event &event) {};
        BasicBody::initSpritesFunction _initSprites = [](
                const mcgwtt::BasicBody::BasicBodyData *data) -> std::tuple<b2Body *, mcgwtt::animationMap> {
            mcgwtt::animationMap a;
            a[&data->_bodies[0]->GetFixtureList()[0]] = mcgwtt::Animation::getStaticAnimation(
                    "ground/ground tile.png");
            return std::make_tuple(data->_bodies[0], a);
        };
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_PLATFORM_H
