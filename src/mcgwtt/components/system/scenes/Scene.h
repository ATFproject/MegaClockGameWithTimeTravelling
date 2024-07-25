// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 5/23/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_SCENE_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_SCENE_H

#include "camera/CameraController.h"

namespace mcgwtt {
    struct Scene {
        bool useSavedCamera{};
        std::string name;
        std::string dir;
        CameraController camera{nullptr, 0};
        std::vector<engine::game::GameObject *> gameObjects;
    };

    void to_json(json &j, const Scene &s);
    void from_json(const json &j, Scene &s);

    class SceneLoader {
    public:
        static Scene load(const std::string &sceneDir);
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_SCENE_H
