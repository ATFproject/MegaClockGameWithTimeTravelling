// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 7/25/24.
//

#include "ContactListener.h"
#include "mcgwtt/game/BasicBody.h"

namespace mcgwtt {
    std::pair<bodyPointerPair, contactFunctionPair> ContactListener::getContactFunctionsAndTypes(b2Contact *contact) {
        auto *typeA = reinterpret_cast<BasicBody *>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        auto *typeB = reinterpret_cast<BasicBody *>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        if (!typeA || !typeB)
            return {};

        auto functionPair = _hitMap.find({typeid(*typeA).name(), typeid(*typeB).name()});

        if (functionPair != _hitMap.end())
            return {{typeA, typeB}, functionPair->second};

        return {};
    }
}
