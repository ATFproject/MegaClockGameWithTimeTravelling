// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 7/25/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_CONTACTLISTENER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_CONTACTLISTENER_H

#include "EngineDef.h"

namespace mcgwtt {
    class BasicBody;

    using beginContactFunction = std::function<void(BasicBody *, BasicBody *)>;
    using endContactFunction = std::function<void(BasicBody *, BasicBody *)>;
    using bodyPointerPair = std::pair<BasicBody *, BasicBody *>;
    using contactFunctionPair = std::pair<beginContactFunction, endContactFunction>;
    using Hitmap = std::map<std::pair<std::string, std::string>, contactFunctionPair>;

    class ContactListener : public b2ContactListener {
    public:
        void BeginContact(b2Contact *contact) override {
            auto functionsAndTypes = getContactFunctionsAndTypes(contact);
            auto function = functionsAndTypes.second.first;
            if (function)
                function(functionsAndTypes.first.first, functionsAndTypes.first.second);
        }

        void EndContact(b2Contact *contact) override {
            auto functionsAndTypes = getContactFunctionsAndTypes(contact);
            auto function = functionsAndTypes.second.second;
            if (function)
                function(functionsAndTypes.first.first, functionsAndTypes.first.second);
        }

        // ORDER OF TypeA and TypeB MUST MATCH THE PARAMETER ORDER IN beginContact AND endContact FUNCTIONS!
        template<class TypeA, class TypeB>
            requires (std::is_base_of_v<BasicBody, TypeA>, std::is_base_of_v<BasicBody, TypeB>)
            void addContactFunctions(const beginContactFunction &beginContact, const endContactFunction &endContact) {
                beginContactFunction beginContactSwapped = [beginContact](BasicBody *A, BasicBody *B) {
                    beginContact(B, A);
                };

                endContactFunction endContactSwapped = [endContact](BasicBody *A, BasicBody *B) {
                    endContact(B, A);
                };

                _hitMap.insert({{typeid(TypeA).name(), typeid(TypeB).name()},
                                {beginContact,         endContact}});
                _hitMap.insert({{typeid(TypeB).name(), typeid(TypeA).name()},
                                {beginContactSwapped,  endContactSwapped}});
            }

    private:
        std::pair<bodyPointerPair, contactFunctionPair> getContactFunctionsAndTypes(b2Contact *contact);

    private:
        Hitmap _hitMap;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_CONTACTLISTENER_H
