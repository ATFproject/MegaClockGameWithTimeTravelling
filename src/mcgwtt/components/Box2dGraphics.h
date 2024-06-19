// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 4/10/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_BOX2DGRAPHICS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_BOX2DGRAPHICS_H

#include <utility>

#include "components/ComponentInterface.h"

namespace mcgwtt {
    class Animation {
    private:
        sf::Clock _clock;

        double _fps = 0;
        std::size_t _frame = 0;
        std::vector<sf::Texture *> _frames;

        void nextFrame() {
            _frame = (_frame + 1) % _frames.size();
        }

    public:
        Animation() = default;

        Animation(double fps, const std::string &spriteSheetName, uint rows, uint columns, uint spriteCount)
                : _fps(fps) {
            sf::Image spriteSheet = engine::resourceHandler.loadRes(
                    new engine::Texture(spriteSheetName))->getTex()->copyToImage();

            uint x = 0, y = 0;
            uint texW = spriteSheet.getSize().x / rows;
            uint texH = spriteSheet.getSize().y / columns;
            for (uint i = 0; i < spriteCount; ++i) {
                auto *temp = new sf::Texture;
                temp->loadFromImage(spriteSheet, sf::IntRect(
                        static_cast<int>(x), static_cast<int>(y), static_cast<int>(texW), static_cast<int>(texH))
                );

                std::string name =
                        "Spritesheet \"" + spriteSheetName + "\" (" + std::to_string(x) + ", " + std::to_string(y) +
                        ")";
                _frames.push_back(engine::resourceHandler.addRes(name, new engine::Texture(temp, name))->getTex());

                x = (x + texW) % spriteSheet.getSize().x;
                if (x == 0 && i != 0)
                    y += texH;
            }
        }

        Animation(double fps, const std::vector<std::string> &texNames)
                : _fps(fps) {
            for (auto &name : texNames) {
                _frames.push_back(engine::resourceHandler.loadRes(new engine::Texture(name))->getTex());
            }
        }

        Animation(double fps, const std::vector<sf::Texture *> &textures)
                : _fps(fps) {
            for (auto &tex : textures) {
                _frames.push_back(tex);
            }
        }

        sf::Texture *curFrame() {
            return _frames[_frame];
        }

        void update() {
            if (_clock.getElapsedTime().asSeconds() > 1.0 / _fps) {
                nextFrame();
                _clock.restart();
            }
        }

        static Animation getStaticAnimation(sf::Texture *singleTexture) {
            Animation res(1, {singleTexture});
            return res;
        }

        static Animation getStaticAnimation(const std::string &texPath) {
            Animation res(1, {texPath});
            return res;
        }
    };

    class BodyGraphics : public engine::components::GraphicsComponent {
    protected:
        sf::RenderWindow *_win{};
        std::map<b2Fixture *, Animation> _animations;
        b2Body *_body{};

        void drawFixture(b2Fixture *fix) {
            sf::ConvexShape shape;
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
