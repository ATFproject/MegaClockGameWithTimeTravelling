// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 25.06.2024.
//

#include "ViewController.h"
#include "window/GameWindow.h"

namespace mcgwtt {
    void ViewController::init(engine::game::Game &game) {
        addObserver(&game);
    }

    void ViewController::onNotify(const engine::Event &event) {
        ENGINE_CHECK_EVENT(engine::game::GameResizeEvent, _size = e->newSize;)
        ENGINE_CHECK_EVENT(PushViewEvent, pushView();)
        ENGINE_CHECK_EVENT(PopViewEvent, popView();)
        ENGINE_CHECK_EVENT(SetViewEvent, setView(e->view);)
        ENGINE_CHECK_EVENT(SetFullScreenViewEvent, setFullScreenView();)

    }

    void ViewController::pushView() {
        _views.push(_view);
    }

    void ViewController::popView() {
        if (_views.empty()) {
            setFullScreenView();
            return;
        }

        _view = _views.top();
        _views.pop();
        notify(window::WindowViewChangedEvent(_view));
    }

    void ViewController::setView(const sf::View &view) {
        _view = view;
        notify(window::WindowViewChangedEvent(_view));
    }

    void ViewController::setFullScreenView() {
        setView(getFullScreenView());
    }

    sf::View ViewController::getFullScreenView() const {
        sf::View view(sf::Vector2f(static_cast<float>(_size.x) / 2.f, static_cast<float>(_size.y) / 2.f),
                      sf::Vector2f(static_cast<float>(_size.x), static_cast<float>(_size.y)));
        return view;
    }

    void ViewController::draw() {}


    AbleToControlViewComponent::AbleToControlViewComponent(ViewController *viewController) {
        addObserver(viewController);
    }

    void AbleToControlViewComponent::setViewController(ViewController *viewController) {
        removeAllObservers();
        addObserver(viewController);
    }
}
