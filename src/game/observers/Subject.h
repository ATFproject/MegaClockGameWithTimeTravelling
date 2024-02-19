//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_SUBJECT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_SUBJECT_H

#include "Observer.h"

#include <list>
#include <algorithm>

namespace game {
    class Subject {
    public:
        void addObserver(Observer *toAdd) {
            _observers.push_back(toAdd);
        }

        void removeObserver(Observer *toRemove) {
            _observers.erase(
                    std::remove(_observers.begin(), _observers.end(), toRemove),
                    _observers.end());
        }

    protected:
        void notify(GameEvent event) {
            for (auto &observer : _observers) {
                observer->onNotify(event);
            }
        }

    private:
        std::list<Observer *> _observers;
    };
} // game

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_SUBJECT_H
