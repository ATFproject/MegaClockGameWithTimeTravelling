// Copyright (c) 2024. ATF project organization!

//
// Created by Timmimin on 08.07.2024.
//

#include "Room.h"

namespace mcgwtt {
    BlockAnimation::BlockAnimation(const std::string &spritesheetName) :
            fps(1), spritesheet(spritesheetName), rows(1), columns(1), frames(1) {}

    Animation BlockAnimation::toAnimation() const {
        if (frames == 1)
            return Animation::getStaticAnimation(spritesheet);
        return {fps, spritesheet, rows, columns, frames};
    }


    void to_json(json &j, const RoomBlock &block) {
        j = json{
                {"x", block.x},
                {"y", block.y},
                {"w", block.w},
                {"h", block.h}
        };
        if (block.anim.frames == 1)
            j["tex"] = block.anim.spritesheet;
        else
            j["animation"] = block.anim;
    }
    void from_json(const json &j, RoomBlock &block) {
        j["x"].get_to(block.x);
        j["y"].get_to(block.y);
        j["w"].get_to(block.w);
        j["h"].get_to(block.h);
        if (j.contains("tex")) {
            std::string tex = j["tex"];
            block.anim = BlockAnimation(tex);
        } else
            j.at("animation").get_to(block.anim);
    }

    Room::Room(sf::RenderWindow *win, GameWorldPhysics *worldPh, float x, float y, const std::string &jsonFilename)
            : BasicBody(win, worldPh, _physicsInit, _physicsTick, _physicsOnNotify, _initSprites),
              _x(x), _y(y), _filename(jsonFilename) {
        std::ifstream f("../bin/Rooms JSONs/" + _filename);
        json::parse(f).get_to(_data);
    }
}
