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
        ActionPerSecond(float targetTimesPerSec, float measureInterval, const std::function<void()> &action)
                : _targetTimesPerSec(targetTimesPerSec), _measureInterval(measureInterval), _action(action) {}

        void tryAction() {
            if (_actionClock.getElapsedTime().asSeconds() + _lastTargetTime >= 1.0 / _targetTimesPerSec) {
                _lastTargetTimeClock.restart();
                _action();

                _actions++;

                _actionClock.restart();
                _lastTargetTime = _lastTargetTimeClock.getElapsedTime().asSeconds();
            }

            if (_actionMeasureClock.getElapsedTime().asSeconds() >= _measureInterval) {
                _measuredActionsPerSec = _actions / _actionMeasureClock.getElapsedTime().asSeconds();
                _actions = 0;
                _actionMeasureClock.restart();
            }
        }

        [[nodiscard]] float getActualActionRate() const {
            return _measuredActionsPerSec;
        }

    private:
        float _targetTimesPerSec, _actions = 0, _measuredActionsPerSec = 0;
        float _lastTargetTime = 0, _measureInterval;

        const std::function<void()> _action;

        sf::Clock _actionClock, _lastTargetTimeClock, _actionMeasureClock;
    };
}
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_TIMER_H
