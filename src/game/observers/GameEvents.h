//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEEVENTS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEEVENTS_H

#include <ostream>
#include "SFML/System.hpp"

namespace game::events {
    enum class GameEventType {
        WINDOW_LOST_FOCUS,
        WINDOW_GAINED_FOCUS,
        WINDOW_RESIZED,
    };

    inline std::string getTypeString(GameEventType type) {
        switch (type) {
            case GameEventType::WINDOW_LOST_FOCUS:
                return "Window lost focus";
            case GameEventType::WINDOW_GAINED_FOCUS:
                return "Window gained focus";
            case GameEventType::WINDOW_RESIZED:
                return "Window resized";
        }

        return "Unnown) type";
    }

    struct GameEvent {
        const GameEventType type;
        static int cnt;

        GameEvent() = delete;
        explicit GameEvent(const GameEventType type) : type(type) {}

        virtual ~GameEvent() = default;
    };

    struct WindowResizeEvent : public GameEvent {
        const sf::Vector2u newSize;
        WindowResizeEvent(unsigned int w, unsigned int h) :
                GameEvent(GameEventType::WINDOW_RESIZED),
                newSize(sf::Vector2u(w, h)) {}
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEEVENTS_H
