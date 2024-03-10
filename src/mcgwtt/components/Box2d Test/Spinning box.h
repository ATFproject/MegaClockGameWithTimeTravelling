//
// Created by livefish on 3/10/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_SPINNING_BOX_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_SPINNING_BOX_H

#include "components/ComponentInterface.h"
#include "observers/Subject.h"
#include "Events.h"

namespace mcgwtt::components {
    struct AddedBlock : public engine::events::Event {
        b2Body *_block;
        explicit AddedBlock(b2Body *block) : _block(block) {}
    };

    struct AddedBox : public engine::events::Event {
        b2Body *_box;
        explicit AddedBox(b2Body *box) : _box(box) {}
    };

    class BoxPhysics : public engine::components::PhysicsComponent {
    private:
        float _x, _y;
        int _maxBoxes, _boxCount;
        sf::Clock _spawnTimer;

    public:
        BoxPhysics(int maxBoxes, float x, float y) : _x(x / 30.0), _y(y / 30.0), _maxBoxes(maxBoxes), _boxCount(0) {
        }

        void init(engine::game::GameObject *gameObject, engine::game::Game &game) override {
            b2Body *ground;
            b2BodyDef bd;
            ground = game._world->CreateBody(&bd);

            bd.type = b2_dynamicBody;
            bd.allowSleep = false;
            bd.position.Set(_x, _y);
            b2Body *body = game._world->CreateBody(&bd);

            b2PolygonShape shape;
            shape.SetAsBox(0.5f, 10.0f, b2Vec2(_x + 10.0f, _y + 0.0f), 0.0);
            body->CreateFixture(&shape, 5.0f);
            shape.SetAsBox(0.5f, 10.0f, b2Vec2(_x + -10.0f, _y + 0.0f), 0.0);
            body->CreateFixture(&shape, 5.0f);
            shape.SetAsBox(10.0f, 0.5f, b2Vec2(_x + 0.0f, _y + 10.0f), 0.0);
            body->CreateFixture(&shape, 5.0f);
            shape.SetAsBox(10.0f, 0.5f, b2Vec2(_x + 0.0f, _y + -10.0f), 0.0);
            body->CreateFixture(&shape, 5.0f);
            notify(AddedBox(body));

            b2RevoluteJointDef jd;
            jd.bodyA = ground;
            jd.bodyB = body;
            jd.localAnchorA.Set(_x + 0.0f, _y + 0.0f);
            jd.localAnchorB.Set(_x + 0.0f, _y + 0.0f);
            jd.referenceAngle = 0.0f;
            jd.motorSpeed = 0.1f * b2_pi;
            jd.maxMotorTorque = 1e8f;
            jd.enableMotor = true;
            game._world->CreateJoint(&jd);
        }

        void tick(engine::game::GameObject *gameObject, engine::game::Game &game) override {
            if (_boxCount < _maxBoxes && _spawnTimer.getElapsedTime().asSeconds() > 0.01) {
                _spawnTimer.restart();
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(_x, _y);
                b2Body *body = game._world->CreateBody(&bd);

                body->GetPosition();
                body->GetAngle();

                b2PolygonShape shape;
                shape.SetAsBox(0.125f, 0.125f);
                body->CreateFixture(&shape, 1.0f);

                notify(AddedBlock(body));

                _boxCount++;
            }
        }
    };

    class BoxGraphics : public engine::components::GraphicsComponent {
    private:
        sf::RenderWindow *_win;
        std::vector<b2Body *> _blocks;
        b2Body *_box {};
        engine::Texture *_blockTex;
        const float SCALE = 30.f;
        sf::Clock _fpsClock;
        int _frames;

    public:
        BoxGraphics(sf::RenderWindow *window, const sf::Color &col) : _win(window), _frames(0) {
            _blockTex = engine::resourceHandler.addRes(new engine::Texture("icon.png"));
        }

        void draw(engine::game::GameObject *gameObject) override {
            if (_fpsClock.getElapsedTime().asSeconds() > 1) {
                std::cout << "FPS: " << _frames << ", boxes: " << _blocks.size() << "\n";
                _frames = 0;
                _fpsClock.restart();
            }

            _frames++;
            _win->clear(sf::Color(89, 90, 107));
            for (auto &block : _blocks) {
                sf::RectangleShape bSprite;
                bSprite.setFillColor(sf::Color(122, 0, 100, 128));
                bSprite.setOutlineColor(sf::Color(122, 0, 100, 240));
                bSprite.setOutlineThickness(1);
                bSprite.setSize(sf::Vector2f(6, 6));
                bSprite.setPosition(block->GetPosition().x * SCALE, block->GetPosition().y * SCALE);
                bSprite.setOrigin(4, 4);
                bSprite.setRotation(block->GetAngle() * 180 / b2_pi);
                _win->draw(bSprite);
            }


            for (auto fix = _box->GetFixtureList(); fix; fix = fix->GetNext()) {
                auto *shape = dynamic_cast<b2PolygonShape *>(fix->GetShape());
                sf::ConvexShape side(4);
                side.setPoint(0, sf::Vector2f(shape->m_vertices[0].x, shape->m_vertices[0].y) * SCALE);
                side.setPoint(1, sf::Vector2f(shape->m_vertices[1].x, shape->m_vertices[1].y) * SCALE);
                side.setPoint(2, sf::Vector2f(shape->m_vertices[2].x, shape->m_vertices[2].y) * SCALE);
                side.setPoint(3, sf::Vector2f(shape->m_vertices[3].x, shape->m_vertices[3].y) * SCALE);
                side.setFillColor(sf::Color::Black);
                side.setRotation(fix->GetBody()->GetAngle() * 180 / b2_pi);
                auto pos = fix->GetBody()->GetPosition();
                side.setPosition(sf::Vector2f(pos.x, pos.y) * SCALE);
                _win->draw(side);
            }
        }

        void onNotify(const engine::events::Event &event) override {
            ENGINE_CHECK_EVENT(AddedBlock, _blocks.push_back(e->_block);)
            ENGINE_CHECK_EVENT(AddedBox, _box = e->_box;)
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_SPINNING_BOX_H
