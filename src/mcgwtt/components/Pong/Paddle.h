//
// Created by livefish on 3/2/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H

#include "components/ComponentInterface.h"
#include "observers/Subject.h"
#include "Events.h"

namespace mcgwtt::components {
    struct PaddleMovedEvent : public engine::events::Event {
        sf::Vector2f newPos;

        PaddleMovedEvent(float x, float y) : newPos(sf::Vector2f(x, y)) {}
    };

    class PaddlePhysics : public engine::components::PhysicsComponent {
    private:
        float _x, _y;
        bool _init = false;
        sf::Keyboard::Key _keyUp, _keyDown;

    public:
        PaddlePhysics(float startX, float startY, sf::Keyboard::Key up, sf::Keyboard::Key down)
                : _x(startX), _y(startY), _keyUp(up), _keyDown(down) {
            notify(PaddleMovedEvent(_x, _y));
        }

        void tick(engine::game::GameObject *gameObject, sf::Time dt, engine::game::Game &game) override {
            if (!_init) {
                notify(PaddleMovedEvent(_x, _y));
                _init = true;
            }

            const int paddleSpeed = 250;
            if (sf::Keyboard::isKeyPressed(_keyUp)) {
                _y -= paddleSpeed * dt.asSeconds();
                _y = std::max(0.f, _y);
                notify(PaddleMovedEvent(_x, _y));
            }
            if (sf::Keyboard::isKeyPressed(_keyDown)) {
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
            auto music = engine::resourceHandler.addRes(new engine::Music("music.mp3"));
            music->setVolume(25);
            music->play();
            paddle.setTexture(*engine::resourceHandler.addRes(new engine::Texture("paddle.png")));
            paddle.setColor(col);
        }

        void draw(engine::game::GameObject *gameObject) override {
            win->draw(paddle);
        }

        void onNotify(const engine::events::Event &event) override {
            ENGINE_CHECK_EVENT(PaddleMovedEvent,
                               sf::Vector2f newCoords = e->newPos;
                                       paddle.setPosition(newCoords.x, newCoords.y);
                                       paddle.setPosition(newCoords.x, newCoords.y);
            )
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H
