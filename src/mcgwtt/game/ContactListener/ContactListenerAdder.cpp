// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 7/25/24.
//

#include "ContactListenerAdder.h"

#include "mcgwtt/game/Player.h"
#include "mcgwtt/game/rooms/Room.h"

namespace mcgwtt {
    ContactListenerAdder::ContactListenerAdder(GameWorldPhysics &physics) {
        addContacts(physics);
    }

    void ContactListenerAdder::addContacts(GameWorldPhysics &physics) {
        physics._contactListener.addContactFunctions<Player, Room>(
                [](BasicBody *player, BasicBody *room) {
                    auto *p = dynamic_cast<Player *>(player);
                    // p->respawn();
                    std::cout << "Player dropped on room block\n";
                },
                [](BasicBody *player, BasicBody *room) {
                    std::cout << "Player dropped off room block\n";
                }
        );
    }
}
