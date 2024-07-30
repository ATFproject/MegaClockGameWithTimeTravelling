// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 7/30/24.
//

#include "Timer.h"

namespace engine {
    ActionPerSecond::ActionPerSecond(float targetTimesPerSec, float measureInterval,
                                     const std::function<void()> &action)
            : _targetTimesPerSec(targetTimesPerSec), _measureInterval(measureInterval), _action(action) {}

    void ActionPerSecond::tryAction() {
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

    float ActionPerSecond::getActualActionRate() const {
        return _measuredActionsPerSec;
    }
}
