// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 7/8/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_ROOM_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_ROOM_H

#include "../game/BasicBody.h"

namespace mcgwtt {
    struct BlockAnimation {
        float fps{};
        std::string spritesheet;
        int rows{}, columns{}, frames{};

        BlockAnimation() = default;
        explicit BlockAnimation(const std::string &spritesheetName);
        [[nodiscard]] Animation toAnimation(const std::string &roomPath) const;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(BlockAnimation, fps, spritesheet, rows, columns, frames)
    };

    struct RoomBlock {
        float x{}, y{}, w{}, h{};
        BlockAnimation anim;
    };

    void to_json(json &j, const RoomBlock &block);
    void from_json(const json &j, RoomBlock &block);

    struct RoomData {
        std::string name;
        float width{}, height{};
        std::vector<RoomBlock> blocks;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(RoomData, name, width, height, blocks)
    };

    class Room : public BasicBody {
    public:
        Room(sf::RenderTarget *target, GameWorldPhysics *worldPh, float x, float y, const std::string &jsonFilename);

    private:
        float _x, _y;
        std::string _filename;
        RoomData _data;

    private:
        physicsInitFunction _physicsInit = [this](engine::game::Game &game) -> bodyFixVecPair {
            b2BodyDef bd;
            bd.type = b2_staticBody;
            bd.position.Set(_x, _y);

            MCGWTT_BASIC_BODY_CREATE_BODY(bd)

            for (auto &block : _data.blocks) {
                b2PolygonShape shape;
                shape.SetAsBox(block.w / 2, block.h / 2,
                               b2Vec2(
                                       block.x - (_data.width - block.w) / 2,
                                       block.y - (_data.height - block.h) / 2
                               ), 0);
                MCGWTT_BASIC_BODY_CREATE_FIXTURE(shape, 1.0f)
            }

            b2PolygonShape shape;
            shape.SetAsBox(_data.width / 2, _data.height / 2,
                           b2Vec2(0, 0), 0);

            b2FixtureDef def;
            def.shape = &shape;
            def.density = 1.0;
            def.filter.maskBits = 0;
            MCGWTT_BASIC_BODY_CREATE_FIXTURE_FROM_DEF(def)

            return res;
        };

        physicsTickFunction _physicsTick = [](engine::game::Game &game) {};
        onNotifyFunction _physicsOnNotify = [](const engine::Event &event) {};

        initSpritesFunction _initSprites = [this](const BasicBodyData *data) -> bodyAnimPair {
            std::string roomPath = _filename.substr(0, _filename.find_last_of('/'));

            std::vector<Animation> animations;
            animations.reserve(_data.blocks.size());

            for (auto &block : _data.blocks) {
                animations.push_back(block.anim.toAnimation(roomPath));
            }

            animations.push_back(Animation::getStaticAnimation("rooms/" + roomPath + "/border.png"));

            return bindAnimations(data, animations);
        };
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_ROOM_H
