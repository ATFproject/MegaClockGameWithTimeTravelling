// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 26.06.2024.
//

#include "BasicBody.h"

namespace mcgwtt {
    BasicBody::BasicBodyData::BasicBodyData(b2Body *body, const std::vector<b2Fixture *> &fix)
            : body(body), fix(fix) {}
    BasicBody::BasicBodyData::BasicBodyData(const BasicBody::bodyFixVecPair &p)
            : body(p.first), fix(p.second) {}


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
        for (auto &func : _onNextTick) {
            func();
        }
        _onNextTick.clear();

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

    void BasicBody::BasicBodyGraphics::draw() {
        BodyGraphics::draw();
    }


    BasicBody::BasicBody(sf::RenderWindow *win, GameWorldPhysics *worldPh, BasicBody::physicsInitFunction &physicsInit,
                         BasicBody::physicsTickFunction &physicsTick, BasicBody::onNotifyFunction &physicsOnNotify,
                         BasicBody::initSpritesFunction &initSprites)
            : _physics(new BasicBodyPhysics(worldPh, physicsInit, physicsTick, physicsOnNotify)),
              _graphics(new BasicBodyGraphics(win, initSprites)) {
        worldPh->addObserver(this);
    }

    void BasicBody::doOnNextTick(const std::function<void()> &function) {
        _physics->_onNextTick.push_back(function);
    }

    void BasicBody::addToGameWindow(window::GameWindow &window) {
        window.addGameObject(nullptr, _physics, _graphics);
    }

    engine::components::PhysicsComponent *BasicBody::getPhysics() {
        return _physics;
    }

    engine::components::GraphicsComponent *BasicBody::getGraphics() {
        return _graphics;
    }
}
