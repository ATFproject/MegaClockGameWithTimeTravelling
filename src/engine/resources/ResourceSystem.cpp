//
// Created by livefish on 2/20/24.
//

#include "Resources.h"

namespace engine{
    std::map<std::string, std::string> extensionFolder = {
            {".png", "images"},
            {".jpg", "images"},
            {".gif", "images"},

            {".wav", "sounds"},
            {".mp3", "sounds"},
            {".ogg", "sounds"},

            {".ttf", "fonts"},
    };

    ResourceHandler resourceHandler;
}
