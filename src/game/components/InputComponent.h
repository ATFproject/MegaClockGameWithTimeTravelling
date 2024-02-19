//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_INPUTCOMPONENT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_INPUTCOMPONENT_H

#include "GameDef.h"

namespace game {
    class InputComponent {
    public:
        virtual void tick(GameObject *gameObject) = 0;
        virtual ~InputComponent() = default;
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_INPUTCOMPONENT_H
