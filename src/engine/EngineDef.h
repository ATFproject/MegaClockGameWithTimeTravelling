// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/20/24.
//
#ifdef _DEBUG
#define _GLIBCXX_DEBUG 1
#endif

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_ENGINEDEF_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_ENGINEDEF_H

#include <vector>
#include <list>
#include <map>

#include <iostream>
#include <fstream>
#include <algorithm>

#include <string>

#include <memory>

#include <chrono>

#include <optional>
#include <variant>

#ifdef WIN32

#include <format>

#else
#include <fmt/format.h>
#endif

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
