// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 4/10/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_BOX2DGRAPHICS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_BOX2DGRAPHICS_H

#include "EngineDef.h"
#include "components/ComponentInterface.h"

namespace mcgwtt {
    class Animation {
    public:
        Animation() = default;
        Animation(double fps, const std::string &spriteSheetName, int rows, int columns, int spriteCount);
        Animation(double fps, const std::vector<std::string> &texNames);
        Animation(double fps, const std::vector<sf::Texture *> &textures);

        void update();

        static Animation getStaticAnimation(sf::Texture *singleTexture);
        static Animation getStaticAnimation(const std::string &texPath);

        sf::Texture *curFrame();

    private:
        void nextFrame();

    private:
        sf::Clock _clock;

        double _fps = 0;
        std::size_t _frame = 0;
        std::vector<sf::Texture *> _frames;
    };

    using animationMap = std::map<b2Fixture *, Animation>;

    class BodyGraphics : public engine::components::GraphicsComponent {
    public:
        explicit BodyGraphics(sf::RenderTarget *target) : _target(target) {}
        void draw() override;

    protected:
        sf::RenderTarget *_target{};
        animationMap _animations;
        b2Body *_body{};

    protected:
        void drawFixture(b2Fixture *fix);
    };
}
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_BOX2DGRAPHICS_H
