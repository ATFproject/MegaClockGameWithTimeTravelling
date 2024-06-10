//
// Created by livefish on 4/10/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_BOX2DGRAPHICS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_BOX2DGRAPHICS_H

#include "components/ComponentInterface.h"

namespace mcgwtt {
    class Animation {
    private:
        sf::Clock _clock;
    public:
        sf::ConvexShape _shape;
        std::vector<sf::Texture *> _frames;
        std::size_t _frame = 0;
        double _fps = 0;

        sf::Texture * curFrame() {
            return _frames[_frame];
        }

        void update() {
            if (_clock.getElapsedTime().asSeconds() > 1.0 / _fps) {
                nextFrame();
                _clock.restart();
            }
        }

        void nextFrame() {
            _frame = (_frame + 1) % _frames.size();
        }
    };

    class BodyGraphics : public engine::components::GraphicsComponent {
    protected:
        sf::RenderWindow *_win{};
        std::map<b2Fixture *, Animation> _animations;
        b2Body *_body{};

        void drawFixture(b2Fixture *fix) {
            auto shape = _animations[fix]._shape;
            shape.setTexture(_animations[fix].curFrame());

            if (fix->GetType() == b2PolygonShape::Type::e_polygon) {
                auto polygon = dynamic_cast<b2PolygonShape *>(fix->GetShape());
                auto pointCount = static_cast<std::size_t>(polygon->m_count);
                shape.setPointCount(pointCount);
                for (std::size_t i = 0; i < pointCount; ++i) {
                    shape.setPoint(i, sf::Vector2f(polygon->m_vertices[i].x, polygon->m_vertices[i].y));
                }
            }

            if (fix->GetType() == b2PolygonShape::Type::e_circle) {
                auto circle = dynamic_cast<b2CircleShape *>(fix->GetShape());
                shape.setPointCount(20);
                sf::CircleShape ref(circle->m_radius, 20);
                for (std::size_t i = 0; i < 20; ++i) {
                    shape.setPoint(i, ref.getPoint(i) +
                                      sf::Vector2f(circle->m_p.x - circle->m_radius, circle->m_p.y - circle->m_radius));
                }
            }
            shape.setPosition(_body->GetPosition().x, _body->GetPosition().y);
            shape.setRotation(_body->GetAngle() / b2_pi * 180.0f);
            _win->draw(shape);
            _animations[fix].update();
        }

    public:
        explicit BodyGraphics(sf::RenderWindow *win) : _win(win) {}

        void draw() override {
            assert(_body);

            for (auto fix = _body->GetFixtureList(); fix != nullptr; fix = fix->GetNext()) {
                drawFixture(fix);
            }
        }
    };
}
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_BOX2DGRAPHICS_H
