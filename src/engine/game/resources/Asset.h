//
// Created by livefish on 2/20/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_ASSET_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_ASSET_H

#include "EngineDef.h"

namespace engine::game::resources {
    extern std::map<std::string, std::string> extensionFolder;
    
    template<typename T>
        std::shared_ptr<T> load(const std::string &FileName) {
            std::string ext = FileName.substr(FileName.find_last_of('.'));
            std::string folder = "../resources/" + extensionFolder[ext] + "/";
            std::string path = folder + FileName;
            auto data = std::make_shared<T>();
            bool res;

            if constexpr (requires { data->loadFromFile(path); }) {
                res = data->loadFromFile(path);
            } else if constexpr (requires { data->openFromFile(path); }) {
                res = data->openFromFile(path);
            } else {
                std::cerr << "No matching load function found!" << std::endl;
                res = false;
            }
            if (!res) {
                std::cerr << "Failed to load \"" << path << "\", exiting'" << std::endl;
                exit(30);
            }
            return data;
        }
} // engine::game::resources

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_ASSET_H
