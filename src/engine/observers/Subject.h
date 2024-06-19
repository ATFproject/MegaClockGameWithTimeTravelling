// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_SUBJECT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_SUBJECT_H

#include "Observer.h"

namespace engine {
    class Subject {
    public:
        void addObserver(Observer *toAdd) {
            if (toAdd != nullptr)
                _observers.push_back(toAdd);
        }

        void removeObserver(Observer *toRemove) {
            _observers.erase(std::remove(_observers.begin(), _observers.end(), toRemove),
                             _observers.end());
        }

        void removeAllObservers() {
            _observers.clear();
        }

    protected:
        void notify(const Event &event) {
            for (auto &observer : _observers) {
                observer->onNotify(event);
            }
        }

    private:
        std::list<Observer *> _observers;
    };
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_SUBJECT_H
