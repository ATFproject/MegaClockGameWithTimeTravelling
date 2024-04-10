//
// Created by livefish on 3/29/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_PLAYER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_PLAYER_H

#include "GameWorld.h"
#include "game/Game.h"

#include "mcgwtt/components/Box2dGraphics.h"

namespace mcgwtt {
    struct PlayerData : engine::events::Event {
        b2Body *_playerBody;
        b2Fixture *_body, *_head;
        PlayerData(b2Body *playerBody, b2Fixture *body, b2Fixture *head)
                : _playerBody(playerBody), _body(body), _head(head) {}
    };


    class PlayerPhysics : public engine::components::PhysicsComponent {
    private:
        b2Body *_body{nullptr};
        float _x, _y;
        const float _w = 0.5, _h = 1.7, _headR = 0.25;

    public:
        PlayerPhysics(GameWorldPhysics *worldPh, float x, float y)
                : _x(x), _y(y) {
            addObserver(worldPh);
        }

        void init(engine::game::GameObject *gameObject, engine::game::Game &game) override {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(_x, _y);

            _body = game._world->CreateBody(&bd);

            b2PolygonShape shapeBody;
            shapeBody.SetAsBox(_w, _h - _headR * 2,
                               b2Vec2(_x, _y + _h), 0);
            auto body = _body->CreateFixture(&shapeBody, 5.0f);

            b2CircleShape shapeHead;
            shapeHead.m_p.Set(_x, _y + _headR);
            shapeHead.m_radius = _headR;
            auto head = _body->CreateFixture(&shapeHead, 5.0f);
            notify(PlayerData(_body, body, head));
        }

        void tick(engine::game::Game &game) override {

        }
    };

    class PlayerGraphics : public BodyGraphics {
    private:
        void initSprites(const PlayerData *prefs) {
            _body = prefs->_playerBody;

            sf::Sprite body;
            body.setTexture(engine::resourceHandler.addRes(new engine::Texture("player body.png"))->getTex());
            _sprites[prefs->_body] = std::move(body);

            sf::Sprite head;
            head.setTexture(engine::resourceHandler.addRes(new engine::Texture("player head.png"))->getTex());
            _sprites[prefs->_head] = std::move(head);
        }
    public:
        explicit PlayerGraphics(sf::RenderWindow *win) : BodyGraphics(win) {}

        void onNotify(const engine::events::Event &event) override {
            ENGINE_CHECK_EVENT(PlayerData, initSprites(e);)
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_PLAYER_H
