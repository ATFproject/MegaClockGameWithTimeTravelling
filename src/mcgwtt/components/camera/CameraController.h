// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 4/5/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H

#include "ViewController.h"

namespace mcgwtt {
    class CameraController : public AbleToControlViewComponent {
    public:
        CameraController(ViewController *viewController, float initialZoom);
        CameraController(const CameraController &old, ViewController *viewController);

        void onNotify(const engine::Event &event) override;
        void draw() override;

    protected:
        void rezoom(float newZoom);
        void resize(float newW, float newH, float x = 0, float y = 0);

        friend void to_json(nlohmann::json &j, const CameraController &camera);
        friend void from_json(const json &j, CameraController &camera);

    protected:
        sf::View _view;
        float _zoom;
        float _saveW{}, _saveH{};

    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H
