//
// Created by livefish on 1/08/24.
//

#include <iostream>

#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

// From https://dvsemenov.ru/c-box2d-v-dvux-slovax/
void testBox2D() {
    b2World world(b2Vec2(0.0f, -10.0f));
    b2BodyDef groundDef;
    groundDef.position.Set(0.0f, -10.0f);
    b2Body *ground = world.CreateBody(&groundDef);
    b2PolygonShape groundShape;
    groundShape.SetAsBox(100.0f / 2, 20.0f / 2);
    ground->CreateFixture(&groundShape, 1.0f);
    b2BodyDef boxDef;
    boxDef.type = b2_dynamicBody;
    boxDef.position.Set(0.0f, 4.0f);
    b2Body *box = world.CreateBody(&boxDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(2.0f / 2, 2.0f / 2);
    b2FixtureDef boxFixDef;
    boxFixDef.shape = &boxShape;
    boxFixDef.density = 1.0f;
    boxFixDef.friction = 0.3f;
    box->CreateFixture(&boxFixDef);
    float time = 1.0f, steps = 100.0f, timeStep = time / steps;
    int velocityIt = 8, positionIt = 3;
    for (int i = 0; i < steps; i++) {
        world.Step(timeStep, velocityIt, positionIt);
        b2Vec2 pos = box->GetPosition();
        std::cout << "Step " << i << ": " << "Block: (" << pos.x << "; " << pos.y << ")\n";
    }
}

int main() {
    testBox2D();

    // set antialiasing level to 16
    sf::ContextSettings winContextSettings(0, 0, 16);
    sf::RenderWindow win(
            sf::VideoMode(800, 600),
            "MegaClockGameWithTimeTravelling 0.0.1 from ATFProject Game studio!",
            sf::Style::Default,
            winContextSettings);
    win.setVerticalSyncEnabled(false);
    win.setActive(true);

    sf::Image icon;
    icon.loadFromFile("../resources/images/icon.png");
    win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    win.setActive(true);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (win.isOpen()) {
        sf::Event event{};
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
            }
        }

        win.clear();
        win.draw(shape);
        win.display();
    }

    return 0;

    return 0;
}
