// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 7/8/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_ROOM_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_ROOM_H

namespace mcgwtt {
    class Room; // Forward declaration

    enum class RoomExitType {
        DEFAULT,
        WALL,
        SIDED_UP,
        SIDED_DOWN,
        SIDED_LEFT,
        SIDED_RIGHT,
        /*Smth else*/
    };

    class RoomExit {
    public:
      uint x = 0, y = 0;
      uint nebX = 0, nebY = 0;
      RoomExitType Type = RoomExitType::DEFAULT;
      Room *Neighbour = nullptr;
    };

    class Room {
    private:
        std::string Name = "Undefined";
        uint Width = 0, Height = 0;

    public:
        int NumOfExits = 0; // Same as "NeighbourRooms" array size
        RoomExit *Exits = nullptr;
        Room() = default;
        ~Room() {
            delete[] Exits;
        }

        void load_from_file(const std::string &BinFileName);
        bool add_neighbour(Room *Neighbour, const int &NeighbourExitNumToConnect, const int &ExitNumToConnect);
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_ROOM_H
