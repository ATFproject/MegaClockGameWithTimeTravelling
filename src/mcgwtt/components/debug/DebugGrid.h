// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 4/10/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGGRID_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGGRID_H

#include "camera/ViewController.h"

namespace mcgwtt {
    class DebugGridGraphics : public AbleToControlViewComponent {
    public:
        DebugGridGraphics(sf::RenderWindow *win, ViewController *viewController);

        void init(engine::game::Game &game) override;
        void onNotify(const engine::Event &event) override;
        void draw() override;

    private:
        void resizeAxis(sf::Vector2f newSize);

    private:
        sf::RectangleShape _xAxis, _yAxis;
        std::vector<sf::RectangleShape> _points;
        sf::RenderWindow *_win;
        const float _lineWidth = 1;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_DEBUGGRID_H
