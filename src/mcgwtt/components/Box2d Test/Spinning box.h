//
// Created by livefish on 3/10/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_SPINNING_BOX_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_SPINNING_BOX_H

#include "components/ComponentInterface.h"
#include "World.h"

namespace mcgwtt::components {
    struct AddedBlock : public engine::events::Event {
        b2Body *_block;
        explicit AddedBlock(b2Body *block) : _block(block) {}
    };

    struct AddedBox : public engine::events::Event {
        b2Body *_box;
        explicit AddedBox(b2Body *box) : _box(box) {}
    };

    struct MotorSpeedChanged : public engine::events::Event {
        double _newSpeed;
        explicit MotorSpeedChanged(double newSpeed) : _newSpeed(newSpeed) {}
    };


    class BoxPhysics : public engine::components::PhysicsComponent {
    private:
        float _x, _y, _speed;
        int _maxBoxes, _boxCount;
        sf::Clock _spawnTimer;
        b2RevoluteJoint *_joint{};
        bool _paused = false;
        sf::Clock _pauseClock;

    public:
        BoxPhysics(WorldPhysics *_worldPh, int maxBoxes, float x, float y) : _x(x / 30.0f), _y(y / 30.0f), _speed(0.1),
                                                                             _maxBoxes(maxBoxes), _boxCount(0) {
            addObserver(_worldPh);
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
            _joint = dynamic_cast<b2RevoluteJoint *>(game._world->CreateJoint(&jd));
        }

        void tick(engine::game::GameObject *gameObject, engine::game::Game &game) override {
            if (_boxCount < _maxBoxes && _spawnTimer.getElapsedTime().asSeconds() > 0.005) {
                _spawnTimer.restart();
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(_x, _y);
                b2Body *body = game._world->CreateBody(&bd);

                b2PolygonShape shape;
                shape.SetAsBox(0.125f, 0.125f);
                body->CreateFixture(&shape, 1.0f);

                notify(AddedBlock(body));

                _boxCount++;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                _joint->SetMotorSpeed(-abs(_joint->GetMotorSpeed()));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                _joint->SetMotorSpeed(abs(_joint->GetMotorSpeed()));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                if (_pauseClock.getElapsedTime().asSeconds() > 0.2) {
                    _pauseClock.restart();
                    _paused = !_paused;
                    notify(GamePausedEvent(_paused));
                }
            }
        }
        void onNotify(const engine::events::Event &event) override {
            ENGINE_CHECK_EVENT(MotorSpeedChanged,
                               _joint->SetMotorSpeed(e->_newSpeed * b2_pi * (_joint->GetMotorSpeed() > 0? 1 : -1));
            )
        }
    };

    class BoxGraphics : public engine::components::GraphicsComponent {
    private:
        sf::RenderWindow *_win;
        std::vector<b2Body *> _blocks;
        b2Body *_box{};
        engine::Texture *_blockTex;
        sf::Color _col;

        const float SCALE = 30.f;
        sf::Clock _fpsClock;
        int _frames, _FPS;

        std::shared_ptr<tgui::Label> fpsLabel;

    public:
        BoxGraphics(sf::RenderWindow *win, window::GameWindow *window, const sf::Color &col)
                : _win(win), _col(col), _frames(0) {
            _blockTex = engine::resourceHandler.addRes(new engine::Texture("icon.png"));

            window->getGui().loadWidgetsFromFile("forms/spinning box/box test.txt");
            auto speedControl = window->getGui().get<tgui::Knob>("Speed knob");
            speedControl->onValueChange([&](float newRotation) {
                notify(MotorSpeedChanged(newRotation / 360));
            });

            fpsLabel = window->getGui().get<tgui::Label>("FPS Label");
        }

        void preDraw(engine::game::GameObject *gameObject) override {
            _win->clear(sf::Color(89, 90, 107));
        }

        void draw(engine::game::GameObject *gameObject) override {
            if (_fpsClock.getElapsedTime().asSeconds() > 0.5) {
                _FPS = _frames * 2;
                std::cout << "FPS: " << _FPS << ", boxes: " << _blocks.size() << "\n";
                _frames = 0;
                _fpsClock.restart();
            }

            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            auto *localTime = std::localtime(&time);
            int y = localTime->tm_year + 1900;
            int m = localTime->tm_mon + 1;
            int d = localTime->tm_mday;
            int h = localTime->tm_hour;
            int min = localTime->tm_min;
            int sec = localTime->tm_sec;
            char buf[256];
            std::sprintf(buf, "Time — %02i:%02i:%02i %02i.%02i.%04i   FPS: %i", h, min, sec, d, m, y, _FPS);
            fpsLabel->setText(buf);

            _frames++;
            sf::RectangleShape bSprite;
            bSprite.setFillColor(sf::Color(122, 0, 100, 128));
            bSprite.setOutlineColor(sf::Color(122, 0, 100, 240));
            bSprite.setOutlineThickness(-1);
            bSprite.setSize(sf::Vector2f(8, 8));
            bSprite.setOrigin(4, 4);

            for (auto &block : _blocks) {
                bSprite.setPosition(block->GetPosition().x * SCALE, block->GetPosition().y * SCALE);
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
                side.setFillColor(_col);
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
