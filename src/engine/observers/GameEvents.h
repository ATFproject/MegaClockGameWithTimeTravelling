//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEEVENTS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEEVENTS_H

#include "EngineDef.h"

namespace engine::events {
    enum class Type {
        WINDOW_LOST_FOCUS,
        WINDOW_GAINED_FOCUS,
        WINDOW_RESIZED,
        WINDOW_MOVE,
        CLOSE
    };

    inline std::string getTypeString(Type type) {
        switch (type) {
            case Type::WINDOW_LOST_FOCUS:
                return "Window lost focus";
            case Type::WINDOW_GAINED_FOCUS:
                return "Window gained focus";
            case Type::WINDOW_RESIZED:
                return "Window resized";
            case Type::CLOSE:
                return "Close event";
            case Type::WINDOW_MOVE:
                return "Window move";
        }

        return "Unnown) type";
    }

    struct Event {
        const Type type;

        Event() = delete;
        explicit Event(const Type type) : type(type) {}
        virtual ~Event() = default;
    };

    struct WindowResizeEvent : public Event {
        const sf::Vector2u newSize;
        WindowResizeEvent(unsigned int w, unsigned int h) :
                Event(Type::WINDOW_RESIZED),
                newSize(sf::Vector2u(w, h)) {}
    };

    struct WindowMoveEvent : public Event {
        sf::Vector2i move;
        WindowMoveEvent(int x, int y) :
                Event(Type::WINDOW_MOVE), move(sf::Vector2i(x, y)) {}
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEEVENTS_H
