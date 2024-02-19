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
        virtual void onNotify(GameEventType type) {};
        virtual void onNotify(GameEvent *event) {}
    };
} // game

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H
