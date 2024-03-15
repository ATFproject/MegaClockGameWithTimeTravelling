//
// Created by livefish on 3/15/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_MENUSCREEN_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_MENUSCREEN_H

#include "components/ComponentInterface.h"
#include "window/GameWindow.h"

#include "../../components/Box2d Test/World.h"
#include "../../components/Box2d Test/Spinning box.h"

namespace mcgwtt::components {
    struct GameStartedEvent : public engine::events::Event {
        engine::game::GameObject *caller;
        explicit GameStartedEvent(engine::game::GameObject *caller) : caller(caller) {}
    };

    class UIController : public engine::components::InputComponent {
    private:
        tgui::Gui &_gui;
        window::GameWindow *_window;
        sf::RenderWindow *_win;

    public:
        UIController(window::GameWindow *window, sf::RenderWindow *win)
                : _gui(window->getGui()), _window(window), _win(win) {
            tgui::setResourcePath("../resources/tgui");
        }

        void onNotify(const engine::events::Event &event) override {
            ENGINE_CHECK_EVENT(GameStartedEvent,
                               _window->removeGameObject(e->caller);
                               auto worldPhysics = new mcgwtt::components::WorldPhysics(*_window,
                                                                                        b2Vec2(0, 9.8),
                                                                                        1 / 165.f, 8, 3);
                               _window->addGameObject(nullptr, worldPhysics, nullptr);
                               _window->addGameObject(nullptr,
                                                      new mcgwtt::components::BoxPhysics(worldPhysics, 1200,
                                                                                         600, 400),
                                                      new mcgwtt::components::BoxGraphics(
                                                              _win, sf::Color(99, 34, 112, 128)));
            )
        }


        void tick(engine::game::GameObject *gameObject, engine::game::Game &game) override {}
    };

    class MenuScreenGraphics : public engine::components::GraphicsComponent {
    private:
        tgui::Gui &_gui;

    public:
        MenuScreenGraphics(window::GameWindow *window, UIController *controller) : _gui(window->getGui()) {
            _gui.loadWidgetsFromFile("forms/main menu/main menu.txt");

            addObserver(controller);
        }

        void init(engine::game::GameObject *gameObject, engine::game::Game &game) override {
            _gui.get<tgui::Button>("Play button")->onPress(
                    [this, gameObject] { notify(GameStartedEvent(gameObject)); }
            );
        }

        ~MenuScreenGraphics() override {
            _gui.remove(_gui.get<tgui::Button>("Play button"));
            _gui.remove(_gui.get<tgui::Picture>("Background"));
            _gui.remove(_gui.get<tgui::Label>("Game title"));
        }

        void draw(engine::game::GameObject *gameObject) override {}
    };
}
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_MENUSCREEN_H
