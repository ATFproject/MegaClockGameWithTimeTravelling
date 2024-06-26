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
        Animation(double fps, const std::string &spriteSheetName, uint rows, uint columns, uint spriteCount);
        Animation(double fps, const std::vector<std::string> &texNames);
        Animation(double fps, const std::vector<sf::Texture *> &textures);

        void update();

        static Animation getStaticAnimation(sf::Texture *singleTexture);
        static Animation getStaticAnimation(const std::string &texPath) {
            Animation res(1, {texPath});
            return res;
        }

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
        explicit BodyGraphics(sf::RenderWindow *win) : _win(win) {}
        void draw() override;

    protected:
        sf::RenderWindow *_win{};
        animationMap _animations;
        b2Body *_body{};

    protected:
        void drawFixture(b2Fixture *fix);
    };
}
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_BOX2DGRAPHICS_H
