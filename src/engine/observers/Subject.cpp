// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 25.06.2024.
//

#include "Subject.h"

namespace engine {
    void Subject::addObserver(Observer *toAdd) {
        if (toAdd != nullptr)
            _observers.push_back(toAdd);
    }
    void Subject::removeObserver(Observer *toRemove) {
        _observers.erase(std::remove(_observers.begin(), _observers.end(), toRemove),
                         _observers.end());
    }
    void Subject::removeAllObservers() {
        _observers.clear();
    }
    void Subject::notify(const Event &event) {
        for (auto &observer : _observers) {
            observer->onNotify(event);
        }
    }
}