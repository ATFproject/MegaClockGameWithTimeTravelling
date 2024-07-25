// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 25.06.2024.
//

#include "Scene.h"

namespace mcgwtt {
    void to_json(json &j, const Scene &s) {
        j["name"] = s.name;
        j["use saved camera"] = s.useSavedCamera;
        j["camera"] = s.camera;
    }

    void from_json(const json &j, Scene &s) {
        j.at("name").get_to(s.name);
        j.at("use saved camera").get_to(s.useSavedCamera);
        j.at("camera").get_to(s.camera);
    }

    Scene SceneLoader::load(const std::string &sceneDir) {
        std::string path = "../bin/scenes/" + sceneDir + "/" + sceneDir + ".json";
        std::ifstream f(path, std::ios::in);
        json scene(json::parse(f));
        Scene s;
        scene.get_to(s);

        s.dir = sceneDir;
        std::cout << "Loading scene \"" << s.name << "\" from " << path << "\n";
        engine::resourceHandler->setLoadPath("scenes/" + sceneDir + "/");
        return s;
    }
}
