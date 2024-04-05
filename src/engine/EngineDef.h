//
// Created by livefish on 2/20/24.
//

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

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <box2d/box2d.h>

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>


#include "external/smartenum.hpp"
#ifdef WIN32
typedef unsigned uint;
#endif

constexpr const float SCALE = 60.f;

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_ENGINEDEF_H
