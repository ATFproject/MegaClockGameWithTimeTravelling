// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 7/25/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_TIMER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_TIMER_H

#include "EngineDef.h"

namespace engine {
    class ActionPerSecond {
    public:
        ActionPerSecond(float targetTimesPerSec, float measureInterval, const std::function<void()> &action);
        void tryAction();
        [[nodiscard]] float getActualActionRate() const;

    private:
        float _targetTimesPerSec, _actions = 0, _measuredActionsPerSec = 0;
        float _lastTargetTime = 0, _measureInterval;

        const std::function<void()> _action;

        sf::Clock _actionClock, _lastTargetTimeClock, _actionMeasureClock;
    };
}
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_TIMER_H
