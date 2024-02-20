//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H

#include "GameEvents.h"

namespace engine::events {
    class Observer {
    public:
        virtual ~Observer() = default;
        virtual void onNotify(Type type) {};
        virtual void onNotify(Event *event) {}
    };
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H
