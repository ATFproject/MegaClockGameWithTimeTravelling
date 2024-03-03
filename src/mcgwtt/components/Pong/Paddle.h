//
// Created by livefish on 3/2/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H

#include "components/ComponentInterface.h"
#include "observers/Subject.h"

namespace mcgwtt::components {
    struct PaddleMovedEvent : public events::Event {
        sf::Vector2f newPos;

        PaddleMovedEvent(float x, float y) :
                Event(events::Type::PADDLE_MOVE), newPos(sf::Vector2f(x, y)) {}
    };

    class PaddlePhysics : public engine::components::PhysicsComponent {
    private:
        float _x, _y;
        bool _init = false;

    public:
        PaddlePhysics(float startX, float startY) : _x(startX), _y(startY) {
            notify(PaddleMovedEvent(_x, _y));
        }

        void tick(engine::game::GameObject *gameObject, sf::Time dt, engine::game::Game &game) override {
            if (!_init) {
                notify(PaddleMovedEvent(_x, _y));
                _init = true;
            }

            const int paddleSpeed = 250;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                _y -= paddleSpeed * dt.asSeconds();
                _y = std::max(0.f, _y);
                notify(PaddleMovedEvent(_x, _y));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                _y += paddleSpeed * dt.asSeconds();
                _y = std::min(game.getSize().y * 1.f - 32, _y);
                notify(PaddleMovedEvent(_x, _y + paddleSpeed * dt.asSeconds()));
            }
        }
    };

    class PaddleGraphics : public engine::components::GraphicsComponent {
    private:
        sf::Sprite paddle;
        sf::RenderWindow *win;

    public:
        PaddleGraphics(sf::RenderWindow *window, const sf::Color &col) : win(window) {
            static sf::Texture paddleTex;
            auto tex = engine::game::resources::load<sf::Texture>("paddle.png");
            paddle.setTexture(*tex);
            paddle.setColor(col);
        }

        void draw(engine::game::GameObject *gameObject) override {
            win->draw(paddle);
        }

        void onNotify(const events::Event &event) override {
            if (event.type == events::Type::PADDLE_MOVE) {
                sf::Vector2f newCoords = dynamic_cast<const PaddleMovedEvent &>(event).newPos;
                paddle.setPosition(newCoords.x, newCoords.y);
            }
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H
