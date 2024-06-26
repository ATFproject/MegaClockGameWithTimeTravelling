// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 26.06.2024.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_BASICBODY_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_BASICBODY_H

#include "Box2dGraphics.h"
#include "system/GameWorld.h"

namespace mcgwtt {
    class BasicBody {
    public:
        struct BasicBodyData : engine::Event {
            std::vector<b2Body *> _bodies;
            explicit BasicBodyData(const std::vector<b2Body *> &bodies) : _bodies(bodies) {}
        };

        using physicsInitFunction = const std::function<std::vector<b2Body *>(engine::game::Game &)>;
        using physicsTickFunction = const std::function<void(engine::game::Game &)>;
        using onNotifyFunction = const std::function<void(const engine::Event &)>;
        using initSpritesFunction = const std::function<std::tuple<b2Body *, animationMap>(
                const BasicBody::BasicBodyData *)>;

        class BasicBodyPhysics : public engine::components::PhysicsComponent {
        public:
            BasicBodyPhysics(GameWorldPhysics *worldPh,
                             physicsInitFunction &init,
                             physicsTickFunction &tick,
                             onNotifyFunction &onNotify
            );

            void init(engine::game::Game &game) override;
            void tick(engine::game::Game &game) override;
            void onNotify(const engine::Event &event) override;

        private:
            physicsInitFunction &_init;
            physicsTickFunction &_tick;
            onNotifyFunction &_onNotify;
        };

        class BasicBodyGraphics : public BodyGraphics {
        public:
            BasicBodyGraphics(sf::RenderWindow *win, initSpritesFunction &initSprites);

            void onNotify(const engine::Event &event) override;

        private:
            initSpritesFunction &_initSprites;
        };

        engine::components::PhysicsComponent *getPhysics();
        engine::components::GraphicsComponent *getGraphics();

    protected:
        BasicBody(sf::RenderWindow *win, GameWorldPhysics *worldPh,
                  physicsInitFunction &physicsInit,
                  physicsTickFunction &physicsTick,
                  onNotifyFunction &physicsOnNotify,
                  initSpritesFunction &initSprites
        );

    private:
        BasicBodyPhysics *_physics;
        BasicBodyGraphics *_graphics;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_BASICBODY_H
