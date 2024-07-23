// Copyright (c) 2024. ATF project organization!

//
// Created by Timmimin on 08.07.2024.
//

#include "Room.h"

namespace mcgwtt {
    BlockAnimation::BlockAnimation(const std::string &spritesheetName) :
            _fps(1), _spritesheetName(spritesheetName), _rows(1), _columns(1), _frames(1) {}

    Animation BlockAnimation::toAnimation() const {
        if (_frames == 1)
            return Animation::getStaticAnimation(_spritesheetName);
        return {_fps, _spritesheetName, _rows, _columns, _frames};
    }

    void to_json(json &j, const BlockAnimation &anim) {
        j = json{
                {"fps",         anim._fps},
                {"spritesheet", anim._spritesheetName},
                {"rows",        anim._rows},
                {"columns",     anim._columns},
                {"frames",      anim._frames}
        };
    }
    void from_json(const json &j, BlockAnimation &anim) {
        j["fps"].get_to(anim._fps);
        j["spritesheet"].get_to(anim._spritesheetName);
        j["rows"].get_to(anim._rows);
        j["columns"].get_to(anim._columns);
        j["frames"].get_to(anim._frames);
    }

    void to_json(json &j, const RoomBlock &block) {
        j = json{
                {"x", block._x},
                {"y", block._y},
                {"w", block._w},
                {"h", block._h}
        };
        if (block._anim._frames == 1)
            j["tex"] = block._anim._spritesheetName;
        else
            j["animation"] = block._anim;
    }
    void from_json(const json &j, RoomBlock &block) {
        j.at("x").get_to(block._x);
        j.at("y").get_to(block._y);
        j.at("w").get_to(block._w);
        j.at("h").get_to(block._h);
        if (j.contains("tex")) {
            std::string tex = j["tex"];
            block._anim = BlockAnimation(tex);
        } else
            j.at("animation").get_to(block._anim);
    }

    void to_json(json &j, const RoomData &data) {
        j = json{
                {"name",   data._name},
                {"width",  data._width},
                {"height", data._height},
        };
        j["blocks"] = json(data._blocks);
    }
    void from_json(const json &j, RoomData &data) {
        j.at("name").get_to(data._name);
        j.at("width").get_to(data._width);
        j.at("height").get_to(data._height);
        j.at("blocks").get_to(data._blocks);

    }

    Room::Room(sf::RenderWindow *win, GameWorldPhysics *worldPh, float x, float y, const std::string &jsonFilename)
            : BasicBody(win, worldPh, _physicsInit, _physicsTick, _physicsOnNotify, _initSprites),
              _x(x), _y(y), _filename(jsonFilename) {
        std::ifstream f("../bin/Rooms JSONs/" + _filename);
        json::parse(f).get_to(_data);
    }
}
