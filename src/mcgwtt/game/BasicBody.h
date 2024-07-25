// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 26.06.2024.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_BASICBODY_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_BASICBODY_H

#include "Box2dGraphics.h"
#include "system/GameWorld.h"

namespace mcgwtt {
    class ContactListener;

    #define MCGWTT_BASIC_BODY_CREATE_BODY(bd) \
                bodyFixVecPair res;           \
                _body = res.first = game._world->CreateBody(&(bd)); \
                _body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    #define MCGWTT_BASIC_BODY_CREATE_FIXTURE_DEF_DENS(shape) \
                res.second.push_back(res.first->CreateFixture(&(shape), 1.0));
    #define MCGWTT_BASIC_BODY_CREATE_FIXTURE(shape, density) \
                res.second.push_back(res.first->CreateFixture(&(shape), (density)));
    #define MCGWTT_BASIC_BODY_CREATE_FIXTURE_FROM_DEF(def) \
                res.second.push_back(res.first->CreateFixture(&def));


    // It was the only solution, I promise. Don't kick my ass for this
    #define MCGWTT_IF_LOCKED_CALL_NEXT_TICK_FUNCTION(name, func)  \
            void name() {                                         \
                if (_body->GetWorld()->IsLocked())                \
                    doOnNextTick(_##name);                        \
                else                                              \
                    _##name();                                    \
            }
    #define MCGWTT_IF_LOCKED_CALL_NEXT_TICK_LAMBDA(name, func)    \
            std::function<void()> _##name = [this]() {            \
                func                                              \
            };                                                    \

    #define MCGWTT_IF_LOCKED_CALL_NEXT_TICK(name, func)           \
        MCGWTT_IF_LOCKED_CALL_NEXT_TICK_LAMBDA(name,func)         \
        MCGWTT_IF_LOCKED_CALL_NEXT_TICK_FUNCTION(name,func)

    #define MCGWTT_IF_LOCKED_CALL_NEXT_TICK_PUBLIC(name, func)    \
        private:                                                  \
            MCGWTT_IF_LOCKED_CALL_NEXT_TICK_LAMBDA(name,func)     \
        public:                                                   \
            MCGWTT_IF_LOCKED_CALL_NEXT_TICK_FUNCTION(name,func)


    class BasicBody : public engine::Observer, public engine::Subject {
    public:
        using bodyFixVecPair = std::pair<b2Body *, std::vector<b2Fixture *>>;
        using bodyAnimPair = std::pair<b2Body *, animationMap>;

        struct BasicBodyData : engine::Event {
            b2Body *body;
            std::vector<b2Fixture *> fix;
            BasicBodyData(b2Body *body, const std::vector<b2Fixture *> &fix);
            explicit BasicBodyData(const bodyFixVecPair &p);
        };

        using physicsInitFunction = const std::function<bodyFixVecPair(engine::game::Game &)>;
        using physicsTickFunction = const std::function<void(engine::game::Game &)>;
        using onNotifyFunction = const std::function<void(const engine::Event &)>;
        using initSpritesFunction = const std::function<bodyAnimPair(const BasicBody::BasicBodyData *)>;

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

        private:
            friend class BasicBody;

            std::vector<std::function<void()>> _onNextTick;
        };

        class BasicBodyGraphics : public BodyGraphics {
        public:
            BasicBodyGraphics(sf::RenderWindow *win, initSpritesFunction &initSprites);

            void onNotify(const engine::Event &event) override;
            void draw() override;

        private:
            initSpritesFunction &_initSprites;
        };

        engine::components::PhysicsComponent *getPhysics();
        engine::components::GraphicsComponent *getGraphics();

        void doOnNextTick(const std::function<void()> &function);

    protected:
        BasicBody(sf::RenderWindow *win, GameWorldPhysics *worldPh,
                  physicsInitFunction &physicsInit,
                  physicsTickFunction &physicsTick,
                  onNotifyFunction &physicsOnNotify,
                  initSpritesFunction &initSprites
        );

        template<typename... Animations>
            bodyAnimPair bindAnimations(const BasicBodyData *data, Animations... animations) {
                animationMap a;
                std::size_t i = 0;
                for (auto &anim : {animations...}) {
                    a[data->fix[i++]] = anim;
                }
                return std::make_pair(_body, a);
            }

        bodyAnimPair bindAnimations(const BasicBodyData *data, const std::vector<Animation> &animations) {
            animationMap a;
            std::size_t i = 0;
            for (auto &anim : animations) {
                a[data->fix[i++]] = anim;
            }
            return std::make_pair(_body, a);
        }


    protected:
        b2Body *_body{nullptr};

        friend class mcgwtt::ContactListener;

    private:
        BasicBodyPhysics *_physics;
        BasicBodyGraphics *_graphics;
    };

}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_BASICBODY_H
