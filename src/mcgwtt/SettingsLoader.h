// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 19.06.2024.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_SETTINGSLOADER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_SETTINGSLOADER_H

#include "EngineDef.h"

namespace mcgwtt {
    inline sf::ContextSettings loadContextSettings() {
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

    inline sf::VideoMode loadVideoMode() {
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

    inline sf::Uint32 loadWindowStyle() {
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

    inline std::string loadWindowTitle() {
        std::ifstream f("../bin/common/settings/settings.json");
        return json::parse(f)["window"]["title"];
    }

    inline void setWindowProperties(sf::RenderWindow &win) {
        std::ifstream f("../bin/common/settings/settings.json");
        auto window = json::parse(f)["window"];
        sf::Image icon;
        std::string icon_name = window["icon path"];
        icon.loadFromFile("../bin/common/textures/" + icon_name);
        win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        win.setPosition(sf::Vector2i(window["position"]["x"], window["position"]["y"]));
        if (window["vertical sync"]) {
            win.setVerticalSyncEnabled(true);
        } else {
            win.setFramerateLimit(window["framerate limit"]);
        }
    }

}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_SETTINGSLOADER_H
