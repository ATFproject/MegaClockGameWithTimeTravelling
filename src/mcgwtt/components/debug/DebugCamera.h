// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 5/23/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGCAMERA_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGCAMERA_H

#include "camera/CameraController.h"

namespace mcgwtt {
    class DebugCamera : public CameraController {
    public:
        DebugCamera(mcgwtt::ViewController *controller, float i);

        void draw() override;
        void onNotify(const engine::Event &event) override;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGCAMERA_H
