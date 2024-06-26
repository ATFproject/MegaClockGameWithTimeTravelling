// Copyright (c) 2024. ATF project organization!

// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "SystemComponents.h"
#include "DebugComponents.h"
#include "CameraComponents.h"

#include "game/Platform.h"
#include "game/Player.h"

#include "system/scenes/Scene.h"

#include "window/GameWindow.h"

#include "settings loader/SettingsLoader.h"

#include "game/BasicBody.h"

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

    window.addGameObject(new mcgwtt::WindowController(&window), nullptr, nullptr);

    auto world = new mcgwtt::GameWorldPhysics(b2Vec2(0, 9.8f), 1 / 165.f, 8, 3);
    window.addGameObject(nullptr, world, nullptr);

    auto view = new mcgwtt::ViewController();
    window.addGameObject(nullptr, nullptr, view);

    auto scene = mcgwtt::SceneLoader::load("test");
    scene._camera.setViewController(view);

    if (scene._useSavedCamera)
        window.addGameObject(nullptr, nullptr, new mcgwtt::CameraController(scene._camera));
    else
        window.addGameObject(nullptr, nullptr, new mcgwtt::DebugCamera(view, 30));

   mcgwtt::Platform platform(&win, world, 0, 6, 4, 1);
   window.addGameObject(nullptr, platform.getPhysics(), platform.getGraphics());

    mcgwtt::Player player(&win, world, 0, 0, 0.5f, 1.7f, 0.25f);
    window.addGameObject(nullptr, player.getPhysics(), player.getGraphics());

    window.addGameObject(nullptr, nullptr, new mcgwtt::DebugGridGraphics(&win, view));

    window.startRendering();
    return 0;
}
