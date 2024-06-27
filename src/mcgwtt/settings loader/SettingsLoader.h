// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 19.06.2024.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_SETTINGSLOADER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_SETTINGSLOADER_H

#include "EngineDef.h"

namespace mcgwtt {
    sf::ContextSettings loadContextSettings();
    sf::VideoMode loadVideoMode();
    sf::Uint32 loadWindowStyle();
    std::string loadWindowTitle();

    void setWindowProperties(sf::RenderWindow &win);
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_SETTINGSLOADER_H
