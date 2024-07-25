// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 7/25/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEPROPERTIES_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEPROPERTIES_H

#include "EngineDef.h"

namespace engine::game {
    struct GameProperties {
        float targetTps, maxFps, gravity;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(GameProperties, targetTps, maxFps, gravity)
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEPROPERTIES_H
