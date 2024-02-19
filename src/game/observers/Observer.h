//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H

#include "GameEvents.h"

#include <exception>

namespace game::events {
    class Observer {
    public:
        virtual ~Observer() = default;
        virtual void onNotify(GameEventType type) = 0;
        virtual void onNotify(GameEvent *event) {
            std::string error = "Received an event object to observer!" + getTypeString(event->type);
            throw std::runtime_error(error);
        };
    };
} // game

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H
