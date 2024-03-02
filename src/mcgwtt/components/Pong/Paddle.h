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
        float x, y;

    public:
        PaddlePhysics(int startX, int startY) : x(startX), y(startY) {
            notify(std::shared_ptr<events::Event>(
                    new PaddleMovedEvent(x, y)
            ));
        }

        void tick(engine::game::GameObject *gameObject, sf::Time dt, engine::game::Game &game) override {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                notify(std::shared_ptr<events::Event>(
                        new PaddleMovedEvent(x, y - 2)
                ));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                notify(std::shared_ptr<events::Event>(
                        new PaddleMovedEvent(x, y + 2)
                ));
            }
        }

        void onNotify(events::Event *event) override {
        }

        void onNotify(events::Type type) override {
        }
    };

    class PaddleGraphics : public engine::components::GraphicsComponent {
    private:
        sf::Sprite paddle;
        sf::RenderWindow *win;

    public:
        explicit PaddleGraphics(sf::RenderWindow *window) : win(window) {
            static sf::Texture paddleTex;
            auto tex = engine::game::resources::load<sf::Texture>("paddle.png");
            paddle.setTexture(*tex);
        }

        void draw(engine::game::GameObject *gameObject) override {
            win->draw(paddle);
        }

        void onNotify(events::Event *event) override {
            if (event->type == events::Type::PADDLE_MOVE) {
                sf::Vector2f newCoords = dynamic_cast<PaddleMovedEvent *>(event)->newPos;
                paddle.setPosition(newCoords.x, newCoords.y);
            }
        }

        void onNotify(events::Type type) override {
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H
