#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

class Arm {
private:
    float l1, l2;       // Lengths
    float theta1, theta2; // Angles (Radians)
    sf::Vector2f origin;  // Base position

public:
    // Constructor
    Arm(float length1, float length2, sf::Vector2f basePos);

    // The Logic (Math)
    void update(sf::Vector2i mousePos);

    // The Rendering
    void draw(sf::RenderWindow& window);
};