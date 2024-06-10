//
// Created by livefish on 5/23/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_SCENE_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_SCENE_H

#include <fstream>
#include <memory>

#include "components/ComponentInterface.h"

namespace mcgwtt {
    class Scene {
    public:
        bool _useSavedCamera;
        std::string _name;
        CameraController _camera{nullptr, 0};
        std::vector<engine::game::GameObject *> _gameObjects{};
    };

    inline void to_json(json &j, const Scene &s) {
        j["name"] = s._name;
        j["use saved camera"] = s._useSavedCamera;
        j["camera"] = s._camera;
    }

    inline void from_json(const json &j, Scene &s) {
        j.at("name").get_to(s._name);
        j.at("use saved camera").get_to(s._useSavedCamera);
        j.at("camera").get_to(s._camera);
    }

    class SceneLoader {
    public:
        static Scene load(const std::string &fileName) {
            std::ifstream f(fileName, std::ios::in);
            json scene(json::parse(f));
            Scene s;
            scene.get_to(s);
            std::cout << "Loading scene: " << s._name << "\n";
            return s;
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_SCENE_H