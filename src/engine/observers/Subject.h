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
        void addObserver(Observer *toAdd);
        void removeObserver(Observer *toRemove);
        void removeAllObservers();

    protected:
        void notify(const Event &event);

    private:
        std::list<Observer *> _observers;
    };
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_SUBJECT_H
