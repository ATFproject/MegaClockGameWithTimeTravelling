//
// Created by livefish on 5/23/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_SCENE_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_SCENE_H

#include <fstream>

#include "components/ComponentInterface.h"

namespace mcgwtt {
    class Scene {
    public:
        std::string _name;
        CameraController *_camera;
        std::vector<engine::game::GameObject *> _gameObjects{};
    };

    inline void to_json(json &j, const Scene &s) {
        j["name"] = s._name;
        j["camera"] = *s._camera;
    }

    inline void from_json(const json &j, Scene &s) {
        j.at("name").get_to(s._name);
        j.at("camera").get_to(*s._camera);
    }

    class SceneLoader {
    public:
        static void load(const std::string &fileName) {
            std::ifstream f(fileName, std::ios::in);
            json scene(json::parse(f));
            Scene s;
            scene.get_to(s);
            std::cout << "Loading scene: " << s._name << "\n";
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_SCENE_H
