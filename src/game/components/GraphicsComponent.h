//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GRAPHICSCOMPONENT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GRAPHICSCOMPONENT_H

#include "GameDef.h"

namespace game {
    class GraphicsComponent {
    public:
        virtual void draw(GameObject *gameObject, const Game &game) = 0;
        virtual ~GraphicsComponent() = default;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GRAPHICSCOMPONENT_H
