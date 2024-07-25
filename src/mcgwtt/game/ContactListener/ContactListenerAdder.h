// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 7/25/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_CONTACTLISTENERADDER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_CONTACTLISTENERADDER_H

#include "ContactListener.h"

namespace mcgwtt {
    class GameWorldPhysics;

    class ContactListenerAdder {
    public:
        explicit ContactListenerAdder(GameWorldPhysics &physics);

    private:
        static void addContacts(GameWorldPhysics &physics);
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_CONTACTLISTENERADDER_H
