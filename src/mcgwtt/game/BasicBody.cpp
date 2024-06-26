// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 26.06.2024.
//

#include "BasicBody.h"

namespace mcgwtt {
    BasicBody::BasicBodyPhysics::BasicBodyPhysics(GameWorldPhysics *worldPh,
                                                  BasicBody::physicsInitFunction &init,
                                                  BasicBody::physicsTickFunction &tick,
                                                  BasicBody::onNotifyFunction &onNotify)
            : _init(init), _tick(tick), _onNotify(onNotify) {
        addObserver(worldPh);
    }

    void BasicBody::BasicBodyPhysics::init(engine::game::Game &game) {
        notify(BasicBodyData(_init(game)));
    }

    void BasicBody::BasicBodyPhysics::tick(engine::game::Game &game) {
        _tick(game);
    }

    void BasicBody::BasicBodyPhysics::onNotify(const engine::Event &event) {
        _onNotify(event);
    }


    BasicBody::BasicBodyGraphics::BasicBodyGraphics(sf::RenderWindow *win, BasicBody::initSpritesFunction &initSprites)
            : BodyGraphics(win), _initSprites(initSprites) {
    }

    void BasicBody::BasicBodyGraphics::onNotify(const engine::Event &event) {
        ENGINE_CHECK_EVENT(BasicBodyData, std::tie(_body, _animations) = _initSprites(e);)
    }


    BasicBody::BasicBody(sf::RenderWindow *win, GameWorldPhysics *worldPh, BasicBody::physicsInitFunction &physicsInit,
                         BasicBody::physicsTickFunction &physicsTick, BasicBody::onNotifyFunction &physicsOnNotify,
                         BasicBody::initSpritesFunction &initSprites)
            : _physics(new BasicBodyPhysics(worldPh, physicsInit, physicsTick, physicsOnNotify)),
              _graphics(new BasicBodyGraphics(win, initSprites)) {}

    engine::components::PhysicsComponent *BasicBody::getPhysics() {
        return _physics;
    }

    engine::components::GraphicsComponent *BasicBody::getGraphics() {
        return _graphics;
    }
}