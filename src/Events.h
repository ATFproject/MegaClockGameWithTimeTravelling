//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_EVENTS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_EVENTS_H

#include "EngineDef.h"

namespace events {
    smart_enum_class(Type,
                     WINDOW_LOST_FOCUS,
                     WINDOW_GAINED_FOCUS,
                     WINDOW_RESIZED,
                     WINDOW_MOVE,

                     PADDLE_MOVE,

                     CLOSE)

    struct Event {
        const Type type;

        Event() = delete;
        explicit Event(const Type type) : type(type) {}
        virtual ~Event() = default;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_EVENTS_H
