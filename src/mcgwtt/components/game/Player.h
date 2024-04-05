//
// Created by livefish on 3/29/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_PLAYER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_PLAYER_H

#include "components/ComponentInterface.h"
#include "GameWorld.h"
#include "game/Game.h"

#include "mcgwtt/box2dsfml/Drawing.h"

namespace mcgwtt::components::game {
    struct PlayerBodyPrefs : engine::events::Event {
        float _w, _h, _headR;
        b2Body *_body;

        PlayerBodyPrefs(float w, float h, float headR, b2Body *body) : _w(w), _h(h), _headR(headR), _body(body) {}
    };


    class PlayerPhysics : public engine::components::PhysicsComponent {
    private:
        b2Body *_body;
        float _x, _y;
        b2Vec2 _speed;
        const float _w = 0.5, _h = 1.7, _headR = 0.25;

    public:
        PlayerPhysics(GameWorldPhysics *worldPh, float x, float y)
                : _body(nullptr), _x(x), _y(y), _speed(0, 0) {
            addObserver(worldPh);
        }

        void init(engine::game::GameObject *gameObject, engine::game::Game &game) override {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(_x, _y);

            _body = game._world->CreateBody(&bd);

            b2PolygonShape shapeBody;
            shapeBody.SetAsBox(_w, _h - _headR * 2,
                               b2Vec2(_x + _w / 2, _y + _h), 0);
            _body->CreateFixture(&shapeBody, 5.0f);

            b2CircleShape shapeHead;
            shapeHead.m_p.Set(_x + _w / 2, _y + _headR);
            shapeHead.m_radius = _headR;
            _body->CreateFixture(&shapeHead, 5.0f);
            notify(PlayerBodyPrefs(_w, _h, _headR, _body));
        }

        void tick(engine::game::GameObject *gameObject, engine::game::Game &game) override {

        }
    };

    class PlayerGraphics : public engine::components::GraphicsComponent {
    private:
        sf::RenderWindow *_win;
        engine::Texture *_bodyTex, *_headTex;
        b2Body *_player = nullptr;
        float _w{}, _h{}, _headR{};

    public:
        explicit PlayerGraphics(sf::RenderWindow *win) : _win(win) {
            _bodyTex = engine::resourceHandler.addRes(new engine::Texture("player body 2.png"));
            _headTex = engine::resourceHandler.addRes(new engine::Texture("player head.png"));
        }

        void draw(engine::game::GameObject *gameObject) override {
            for (auto fix = _player->GetFixtureList(); fix; fix = fix->GetNext()) {
                auto tex = fix->GetShape()->GetType() == b2Shape::Type::e_circle ? _headTex : _bodyTex;
                drawing::drawFixture(_win, *fix, tex->getTex());
            }
        }

        void onNotify(const engine::events::Event &event) override {
            ENGINE_CHECK_EVENT(PlayerBodyPrefs, _w = e->_w; _h = e->_h; _headR = e->_headR; _player = e->_body;)
        }
    };
}
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_PLAYER_H
