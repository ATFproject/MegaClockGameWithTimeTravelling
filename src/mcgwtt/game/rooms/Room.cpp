// Copyright (c) 2024. ATF project organization!

//
// Created by Timmimin on 08.07.2024.
//

#include <string>
#include <fstream>
#include "Room.h"
#include "EngineDef.h"

void mcgwtt::Room::load_from_file(const std::string &BinFileName) {
    const std::string path = "../bin/Rooms JSONs/" + BinFileName;
    std::ifstream f(path, std::ios::in);
    json loadedRoom(json::parse(f));
    // Fill data
    loadedRoom.at("name").get_to(Name);
    loadedRoom.at("width").get_to(Width);
    loadedRoom.at("height").get_to(Height);

    loadedRoom.at("numOfExits").get_to(NumOfExits);
    if (NumOfExits != 0) {
        Exits = new RoomExit[NumOfExits];
    }
}

bool mcgwtt::Room::add_neighbour(mcgwtt::Room *Neighbour, const int &NeighbourExitNumToConnect,
                                 const int &ExitNumToConnect) {
    // Check if out of array size
    if (NeighbourExitNumToConnect < 0 || NeighbourExitNumToConnect >= Neighbour->NumOfExits
        || ExitNumToConnect < 0 || ExitNumToConnect >= NumOfExits) {
        return false;
    }
    // Check if out of space left
    if (Exits[ExitNumToConnect].Neighbour != nullptr) {
        return false;
    }

    Exits[ExitNumToConnect].Neighbour = Neighbour;
    Exits[ExitNumToConnect].nebX = Neighbour->Exits[NeighbourExitNumToConnect].x;
    Exits[ExitNumToConnect].nebY = Neighbour->Exits[NeighbourExitNumToConnect].y;

    return true;
}
