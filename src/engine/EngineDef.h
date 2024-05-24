//
// Created by livefish on 2/20/24.
//
#ifdef _DEBUG
#define _GLIBCXX_DEBUG 1
#endif

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_ENGINEDEF_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_ENGINEDEF_H

#include <string>

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <chrono>
#include <optional>
#include <variant>
#include <format>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <box2d/box2d.h>

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "external/smartenum.hpp"
#ifdef WIN32
typedef unsigned uint;
#endif

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_ENGINEDEF_H
