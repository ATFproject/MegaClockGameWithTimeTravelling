//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_SUBJECT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_SUBJECT_H

#include "Observer.h"

namespace engine::events {
    class Subject {
    public:
        void addObserver(Observer *toAdd) {
            _observers.push_back(toAdd);
        }

        void removeObserver(Observer *toRemove) {
            _observers.erase(std::remove(_observers.begin(), _observers.end(), toRemove),
                    _observers.end());
        }

    protected:
        void notify(const Type &type) {
            for (auto &observer : _observers) {
                observer->onNotify(type);
            }
        }

        void notify(const std::shared_ptr<events::Event>& event) {
            for (auto &observer : _observers) {
                observer->onNotify(event.get());
            }
        }

    private:
        std::list<Observer *> _observers;
    };
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_SUBJECT_H
