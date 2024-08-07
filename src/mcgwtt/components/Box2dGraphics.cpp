// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 25.06.2024.
//

#include "Box2dGraphics.h"

namespace mcgwtt {
    Animation::Animation(double fps, const std::string &spriteSheetName, int rows, int columns, int spriteCount)
            : _fps(fps) {
        sf::Image spriteSheet = engine::resourceHandler->loadRes(
                new engine::Texture(spriteSheetName))->getTex()->copyToImage();

        int x = 0, y = 0,
                sizeX = static_cast<int>(spriteSheet.getSize().x),
                sizeY = static_cast<int>(spriteSheet.getSize().y),
                texW = sizeX / rows,
                texH = sizeY / columns;

        for (int i = 0; i < spriteCount; ++i) {
            auto *temp = new sf::Texture;
            temp->loadFromImage(spriteSheet, sf::IntRect(x, y, texW, texH));

            std::string name =
                    "Spritesheet \"" + spriteSheetName + "\" (" + std::to_string(x) + ", " + std::to_string(y) +
                    ")";
            _frames.push_back(engine::resourceHandler->addRes(name, new engine::Texture(temp, name))->getTex());

            x = (x + texW) % sizeX;
            if (x == 0 && i != 0)
                y += texH;
        }
    }

    Animation::Animation(double fps, const std::vector<std::string> &texNames)
            : _fps(fps) {
        for (auto &name : texNames) {
            _frames.push_back(engine::resourceHandler->loadRes(new engine::Texture(name))->getTex());
        }
    }

    Animation::Animation(double fps, const std::vector<sf::Texture *> &textures)
            : _fps(fps) {
        for (auto &tex : textures) {
            _frames.push_back(tex);
        }
    }

    sf::Texture *Animation::curFrame() {
        return _frames[_frame];
    }

    void Animation::update() {
        if (_clock.getElapsedTime().asSeconds() > 1.0 / _fps) {
            nextFrame();
            _clock.restart();
        }
    }

    Animation Animation::getStaticAnimation(sf::Texture *singleTexture) {
        Animation res(1, {singleTexture});
        return res;
    }

    Animation Animation::getStaticAnimation(const std::string &texPath) {
        Animation res(1, {texPath});
        return res;
    }

    void Animation::nextFrame() {
        _frame = (_frame + 1) % _frames.size();
    }

    void BodyGraphics::drawFixture(b2Fixture *fix) {
        sf::ConvexShape shape;
        assert(_animations.contains(fix));
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

    void BodyGraphics::draw() {
        assert(_body);

        for (auto fix = _body->GetFixtureList(); fix != nullptr; fix = fix->GetNext()) {
            drawFixture(fix);
        }
    }
}
