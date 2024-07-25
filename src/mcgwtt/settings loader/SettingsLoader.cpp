// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 25.06.2024.
//

#include "SettingsLoader.h"

namespace mcgwtt {
    sf::ContextSettings loadContextSettings() {
        std::ifstream f("../bin/common/settings/settings.json");
        auto context = json::parse(f)["context"];

        sf::ContextSettings settings;
        settings.majorVersion = context["OpenGL version"]["major"];
        settings.minorVersion = context["OpenGL version"]["minor"];

        settings.antialiasingLevel = context["antialiasing"];
        settings.depthBits = context["depth bits"];
        settings.stencilBits = context["stenсil bits"];

        return settings;
    }

    sf::VideoMode loadVideoMode() {
        std::ifstream f("../bin/common/settings/settings.json");
        auto window = json::parse(f)["window"]["mode"];
        if (window["use fullscreen mode"]) {
            return sf::VideoMode::getFullscreenModes()[0];
        }
        sf::VideoMode mode;
        mode.width = window["width"];
        mode.height = window["height"];
        mode.bitsPerPixel = window["bits per pixel"];

        return mode;
    }

    sf::Uint32 loadWindowStyle() {
        std::ifstream f("../bin/common/settings/settings.json");
        auto style = json::parse(f)["window"]["style"];
        if (style["None"]) {
            return sf::Style::None;
        }
        if (style["Default"]) {
            return sf::Style::Default;
        }
        if (style["Fullscreen"]) {
            return sf::Style::Fullscreen;
        }

        return style["Titlebar"].get<sf::Uint32>() |
               style["Resize"].get<sf::Uint32>() |
               style["Close"].get<sf::Uint32>();
    }

    std::string loadWindowTitle() {
        std::ifstream f("../bin/common/settings/settings.json");
        return json::parse(f)["window"]["title"];
    }

    void setWindowProperties(sf::RenderWindow &win) {
        std::ifstream f("../bin/common/settings/settings.json");
        auto window = json::parse(f)["window"];
        sf::Image icon;
        std::string iconName = window["icon path"];
        icon.loadFromFile("../bin/common/textures/" + iconName);
        win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        win.setPosition(sf::Vector2i(window["position"]["x"], window["position"]["y"]));

        // framerate is handled manually inside the game loop
        win.setVerticalSyncEnabled(false);
        win.setFramerateLimit(0);
    }

    void setGameProperties(window::GameWindow &gameWin) {
        std::ifstream f("../bin/common/settings/settings.json");
        auto game = json::parse(f)["game"];
        engine::game::GameProperties props = game;
        gameWin.setProperties(props);
    }
}
