//
// Created by livefish on 2/20/24.
//

#include "Asset.h"

namespace engine::game::resources {
    std::map<std::string, std::string> extensionFolder = {
            {".png", "images"},
            {".jpg", "images"},
            {".gif", "images"},

            {".wav", "sounds"},
            {".mp3", "sounds"},
            {".ogg", "sounds"},

            {".ttf", "fonts"},
    };
}
