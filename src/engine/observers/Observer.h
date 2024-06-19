// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H

#include "Events.h"


/* Usage:
   ENGINE_CHECK_EVENT(PaddleMovedEvent,
               sf::Vector2f newCoords = e->newPos;
               paddle.setPosition(newCoords.x, newCoords.y);
               paddle.setPosition(newCoords.x, newCoords.y);
            )
 */
#define ENGINE_CHECK_EVENT(EVENT_TYPE, code) \
            if (auto e = dynamic_cast<const EVENT_TYPE *>(&event)) { \
                code                      \
                return;                   \
            }

namespace engine {
    class Observer {
    public:
        virtual ~Observer() = default;
        virtual void onNotify(const Event &event) {};
    };
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_OBSERVER_H
