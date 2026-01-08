#include <SFML/Graphics.hpp>
#include "Arm.h"

int main() {
    // Create Window with Anti-Aliasing for smooth lines
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Robot Arm", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    // Initialize Arm at center of screen
    Arm robotArm(200.0f, 150.0f, sf::Vector2f(400.0f, 300.0f));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        robotArm.update(mousePos);

        // Render
        window.clear(sf::Color(30, 30, 30)); // Dark Grey
        robotArm.draw(window);
        window.display();
    }

    return 0;
}