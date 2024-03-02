//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H

#include "Events.h"

namespace engine {
    class Observer {
    public:
        virtual ~Observer() = default;
        virtual void onNotifyType(events::Type type) {};
        virtual void onNotify(const events::Event *event) {}
    };
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H
