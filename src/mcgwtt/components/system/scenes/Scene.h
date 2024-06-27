// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 5/23/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_SCENE_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_SCENE_H

#include "camera/CameraController.h"

namespace mcgwtt {
    struct Scene {
        bool _useSavedCamera{};
        std::string _name;
        std::string _dir;
        CameraController _camera{nullptr, 0};
        std::vector<engine::game::GameObject *> _gameObjects{};
    };

    void to_json(json &j, const Scene &s);
    void from_json(const json &j, Scene &s);

    class SceneLoader {
    public:
        static Scene load(const std::string &sceneDir);
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_SCENE_H
