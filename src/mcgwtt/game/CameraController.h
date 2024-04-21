//
// Created by livefish on 4/5/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H

#include "components/ComponentInterface.h"
#include "game/Game.h"


namespace mcgwtt {
    class CameraController : public AbleToControlViewComponent {
    private:
        float _zoom;

        void resize(float newW, float newH) {
            sf::View view;
            view.setCenter(0, 0);
            view.setSize(newW / _zoom, newH / _zoom);
            notify(SetViewEvent(view));
        }

    public:
        CameraController(ViewController *viewController, float initialZoom)
                : AbleToControlViewComponent(viewController), _zoom(initialZoom) {
        }

        void draw() override {
        }

        void onNotify(const engine::Event &event) override {
            ENGINE_CHECK_EVENT(engine::game::GameResizeEvent, resize(e->_newSize.x, e->_newSize.y);)
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_CAMERACONTROLLER_H
