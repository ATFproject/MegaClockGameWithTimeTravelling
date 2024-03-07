//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_EVENTS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_EVENTS_H

#include "EngineDef.h"

namespace engine::events {
    struct Event {
    protected:
        Event() = default;
    public:
        virtual ~Event() = default;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_EVENTS_H
