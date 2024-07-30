// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 3/29/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_PLAYER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_PLAYER_H

#include "BasicBody.h"

namespace mcgwtt {
    class Player : public BasicBody {
    public:
        Player(sf::RenderWindow *win, GameWorldPhysics *worldPh,
               float x, float y, float w, float h, float headR)
                : BasicBody(win, worldPh, _physicsInit, _physicsTick, _physicsOnNotify, _initSprites),
                  _x(x), _y(y), _spawnX(x), _spawnY(y), _w(w), _h(h), _headR(headR) {}

    private:
        physicsInitFunction _physicsInit = [this](engine::game::Game &game) -> bodyFixVecPair {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(_x, _y);

            MCGWTT_BASIC_BODY_CREATE_BODY(bd)

            _body->GetUserData();

            b2PolygonShape shapeBody;
            shapeBody.SetAsBox(_w, _h - _headR * 2, b2Vec2(_x, _y + _h), 0);
            MCGWTT_BASIC_BODY_CREATE_FIXTURE(shapeBody, 5.0f)

            b2CircleShape shapeHead;
            shapeHead.m_p.Set(_x, _y + _headR);
            shapeHead.m_radius = _headR;
            MCGWTT_BASIC_BODY_CREATE_FIXTURE(shapeHead, 2.0f)

            return res;
        };

        physicsTickFunction _physicsTick = [this](engine::game::Game &game) {
            if (game.isKeyPressed(sf::Keyboard::Scancode::D)) {
                _body->SetLinearVelocity(b2Vec2(3, _body->GetLinearVelocity().y));
            }
            if (game.isKeyPressed(sf::Keyboard::Scancode::A)) {
                _body->SetLinearVelocity(b2Vec2(-3, _body->GetLinearVelocity().y));
            }
            if (game.wasKeyClicked(sf::Keyboard::Scancode::R)) {
                respawn();
            }
        };

        onNotifyFunction _physicsOnNotify = [this](const engine::Event &event) {
        };


        initSpritesFunction _initSprites = [this](const BasicBodyData *data) -> bodyAnimPair {
            return bindAnimations(
                    data,
                    Animation(3, "common/textures/player/player body.png", 4, 2, 6),
                    Animation::getStaticAnimation("common/textures/player/player head.png")
            );
        };


        MCGWTT_IF_LOCKED_CALL_NEXT_TICK(respawn, {
            _body->SetTransform(b2Vec2(_spawnX, _spawnY), 0);
            _body->SetLinearVelocity(b2Vec2_zero);
            _body->SetAngularVelocity(0);
        })

    private:
        float _x, _y, _spawnX, _spawnY;
        const float _w, _h, _headR;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_PLAYER_H
