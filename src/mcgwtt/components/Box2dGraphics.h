//
// Created by livefish on 4/10/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_BOX2DGRAPHICS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_BOX2DGRAPHICS_H

#include "components/ComponentInterface.h"

namespace mcgwtt {
    class BodyGraphics : public engine::components::GraphicsComponent {
    protected:
        sf::RenderWindow *_win{};
        std::map<b2Fixture *, sf::Sprite> _sprites;
        b2Body *_body{};

        void drawFixture(b2Fixture *fix) {
            auto sprite = _sprites[fix];

            float x, y, w, h;
            x = y = w = h = 0;
            float texW = static_cast<float>(sprite.getTexture()->getSize().x);
            float texH = static_cast<float>(sprite.getTexture()->getSize().y);

            if (fix->GetType() == b2PolygonShape::Type::e_polygon) {
                auto shape = dynamic_cast<b2PolygonShape *>(fix->GetShape());
                assert(shape);
                x = shape->m_vertices[0].x;
                y = shape->m_vertices[0].y;
                w = shape->m_vertices[1].x - shape->m_vertices[0].x;
                h = shape->m_vertices[2].y - shape->m_vertices[1].y;
            }

            if (fix->GetType() == b2PolygonShape::Type::e_circle) {
                auto shape = dynamic_cast<b2CircleShape *>(fix->GetShape());
                assert(shape);
                x = shape->m_p.x - shape->m_radius;
                y = shape->m_p.y - shape->m_radius;
                w = h = shape->m_radius * 2;
            }

            sprite.setScale(w / texW, h / texH); // set texture w and h to equal w and h from fixture
            sprite.setPosition(sf::Vector2f(x, y));
            sprite.move(sf::Vector2f(fix->GetBody()->GetPosition().x, fix->GetBody()->GetPosition().y));
            _win->draw(sprite);
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
