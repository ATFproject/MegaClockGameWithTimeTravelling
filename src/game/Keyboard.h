//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_KEYBOARD_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_KEYBOARD_H

#include "SFML/Window/Keyboard.hpp"

#include <cstring>

namespace game {
    class Keyboard {
    public:
        bool _keys[256]{};

        void reset() {
            std::memset(_keys, 0, 256);
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_KEYBOARD_H
