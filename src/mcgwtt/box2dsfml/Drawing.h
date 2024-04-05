//
// Created by livefish on 3/29/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_DRAWING_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_DRAWING_H

#include "EngineDef.h"

namespace mcgwtt::drawing {
    void drawFixture(sf::RenderWindow *win, b2Fixture &fix, const sf::Texture &tex) {
        sf::Sprite sprite;
        sprite.setTexture(tex);

        float x, y, w, h;
        x = y = w = h = 0;
        float texW = tex.getSize().x;
        float texH = tex.getSize().y;

        if (fix.GetType() == b2PolygonShape::Type::e_polygon) {
            auto shape = dynamic_cast<b2PolygonShape *>(fix.GetShape());
            x = shape->m_vertices[0].x;
            y = shape->m_vertices[0].y;
            w = shape->m_vertices[1].x - shape->m_vertices[0].x;
            h = shape->m_vertices[2].y - shape->m_vertices[1].y;
        }

        if (fix.GetType() == b2PolygonShape::Type::e_circle) {
            auto shape = dynamic_cast<b2CircleShape *>(fix.GetShape());
            x = shape->m_p.x - shape->m_radius;
            y = shape->m_p.y - shape->m_radius;
            w = h = shape->m_radius * 2;
        }

        sprite.setScale(w / texW, h / texH); // set texture w and h to equal w and h from fixture
        sprite.scale(SCALE, SCALE);
        sprite.setPosition(sf::Vector2f(x, y) * SCALE);
        sprite.move(sf::Vector2f(fix.GetBody()->GetPosition().x, fix.GetBody()->GetPosition().y) * SCALE);
        win->draw(sprite);
    }
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_DRAWING_H
