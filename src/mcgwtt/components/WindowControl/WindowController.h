//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLLER_H

#include "components/ComponentInterface.h"
#include "observers/Subject.h"

#include "engine/window/GameWindow.h"

namespace mcgwtt::components {
    class WindowController : public engine::components::InputComponent {
    private:
        sf::RenderWindow *_window;
    public:
        WindowController(window::GameWindow *win, sf::RenderWindow *window);
        void onNotify(const engine::events::Event &event) override;
        void tick(engine::game::GameObject *gameObject, engine::game::Game &game) override;
    };
}
// engine::components

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLLER_H
