//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H

#include "GameEvents.h"

namespace game {
    class Observer {
    public:
        virtual ~Observer() = default;
        virtual void onNotify(const GameEvent &event) = 0;
    };
} // game

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H
