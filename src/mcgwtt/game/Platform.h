//
// Created by livefish on 4/10/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_PLATFORM_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_PLATFORM_H

#include "mcgwtt/components/Box2dGraphics.h"

#include "system/GameWorld.h"

namespace mcgwtt {
    struct PlatformData : engine::Event {
        b2Body *_body;
        b2Fixture *_fixture;
        PlatformData(b2Body *body, b2Fixture *fixture) : _body(body), _fixture(fixture) {}
    };

    class PlatformPhysics : public engine::components::PhysicsComponent {
    private:
        b2Body *_body{};
        b2Fixture *_fixture{};

        float _x, _y, _w, _h;

    public:
        PlatformPhysics(GameWorldPhysics *worldPh, float x, float y, float w, float h) :
                _x(x), _y(y), _w(w), _h(h) {
            addObserver(worldPh);
        }

        void init(engine::game::Game &game) override {
            b2BodyDef bd;
            bd.type = b2_kinematicBody;
            bd.position.Set(_x, _y);
            bd.gravityScale = 0;
            bd.fixedRotation = true;
            _body = game._world->CreateBody(&bd);

            b2PolygonShape shape;
            shape.SetAsBox(_w, _h, b2Vec2(_x, _y), 0);
            _fixture = _body->CreateFixture(&shape, 5.0f);
            notify(PlatformData(_body, _fixture));
        }

        void tick(engine::game::Game &game) override {}
    };

    class PlatformGraphics : public BodyGraphics {
    private:
        void initSprites(const PlatformData *prefs) {
            _body = prefs->_body;
            sf::ConvexShape body;
            body.setTexture(engine::resourceHandler.addRes(new engine::Texture("ground tile.png"))->getTex());
            _shapes[prefs->_fixture] = std::move(body);
        }
    public:
        explicit PlatformGraphics(sf::RenderWindow *win) : BodyGraphics(win) {}

        void onNotify(const engine::Event &event) override {
            ENGINE_CHECK_EVENT(PlatformData, initSprites(e);)
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_PLATFORM_H
