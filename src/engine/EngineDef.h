// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/20/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_ENGINEDEF_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_ENGINEDEF_H

#include <vector>
#include <list>
#include <map>
#include <stack>

#include <iostream>
#include <fstream>
#include <algorithm>

#include <string>

#include <memory>

#include <chrono>

#include <optional>
#include <variant>


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <box2d/box2d.h>

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

#ifdef WIN32
typedef unsigned uint;
#endif

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_ENGINEDEF_H
