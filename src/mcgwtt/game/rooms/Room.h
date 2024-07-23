// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 7/8/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_ROOM_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_ROOM_H

#include "../game/BasicBody.h"

namespace mcgwtt {
    struct BlockAnimation {
        float _fps{};
        std::string _spritesheetName;
        int _rows{}, _columns{}, _frames{};

        BlockAnimation() = default;
        explicit BlockAnimation(const std::string &spritesheetName);
        [[nodiscard]] Animation toAnimation() const;
    };

    void to_json(json &j, const BlockAnimation &anim);
    void from_json(const json &j, BlockAnimation &anim);

    struct RoomBlock {
        float _x{}, _y{}, _w{}, _h{};
        BlockAnimation _anim;
    };

    void to_json(json &j, const RoomBlock &block);
    void from_json(const json &j, RoomBlock &block);

    struct RoomData {
        std::string _name;
        float _width{}, _height{};
        std::vector<RoomBlock> _blocks;
    };

    void to_json(json &j, const RoomData &data);
    void from_json(const json &j, RoomData &data);

    class Room : public BasicBody {
    public:
        Room(sf::RenderWindow *win, GameWorldPhysics *worldPh, float x, float y, const std::string &jsonFilename);

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

            for (auto &block : _data._blocks) {
                b2PolygonShape shape;
                shape.SetAsBox(block._w / 2, block._h / 2,
                               b2Vec2(
                                       block._x - (_data._width - block._w) / 2,
                                       block._y - (_data._height - block._h) / 2
                               ), 0);
                MCGWTT_BASIC_BODY_CREATE_FIXTURE(shape, 1.0f)
            }

            b2PolygonShape shape;
            shape.SetAsBox(_data._width / 2, _data._height / 2,
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
            std::vector<Animation> animations;
            animations.reserve(_data._blocks.size());

            for (auto &block : _data._blocks) {
                animations.push_back(block._anim.toAnimation());
            }

            animations.push_back(Animation::getStaticAnimation("rooms/border.png"));

            return bindAnimations(data, animations);
        };
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_ROOM_H
