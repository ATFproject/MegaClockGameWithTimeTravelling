// Copyright (c) 2024. ATF project organization!

// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "SystemComponents.h"
#include "DebugComponents.h"
#include "CameraComponents.h"

#include "settings loader/SettingsLoader.h"
#include "system/scenes/Scene.h"

#include "game/Player.h"
#include "game/rooms/Room.h"

int main() {
    sf::RenderWindow win(
            mcgwtt::loadVideoMode(),
            mcgwtt::loadWindowTitle(),
            mcgwtt::loadWindowStyle(),
            mcgwtt::loadContextSettings()
    );
    mcgwtt::setWindowProperties(win);
    win.setActive(true);

    window::GameWindow window(&win);
    mcgwtt::setGameProperties(window);

    window.addGameObject(new mcgwtt::WindowController(&window), nullptr, nullptr);

    auto world = new mcgwtt::GameWorldPhysics(
            b2Vec2(0, window.getProperties().gravity),
            1 / window.getProperties().targetTps,
            8, 3
    );

    window.addGameObject(nullptr, world, nullptr);

    auto view = new mcgwtt::ViewController();
    window.addGameObject(nullptr, nullptr, view);

    auto scene = mcgwtt::SceneLoader::load("test");
    scene._camera.setViewController(view);

    if (scene._useSavedCamera)
        window.addGameObject(nullptr, nullptr, new mcgwtt::CameraController(scene._camera));
    else
        window.addGameObject(nullptr, nullptr, new mcgwtt::DebugCamera(view, 30));

    mcgwtt::Player player(&win, world, 4, -8, 0.5f, 1.7f, 0.25f);
    window.addGameObject(nullptr, player.getPhysics(), player.getGraphics());

    mcgwtt::Room room(&win, world, 0, 0, "Main Room Samples/main_room_1.json");
    window.addGameObject(nullptr, room.getPhysics(), room.getGraphics());

    window.addGameObject(nullptr, nullptr, new mcgwtt::DebugGridGraphics(&win, view));

    window.startRendering();
    return 0;
}
