#include "Arm.h"
#include <algorithm> // For std::max, std::min

// Constructor
Arm::Arm(float length1, float length2, sf::Vector2f basePos) {
    l1 = length1;
    l2 = length2;
    origin = basePos;
    theta1 = 0;
    theta2 = 0;
}

void Arm::update(sf::Vector2i mousePos) {
    // 1. Coordinate Shift (Mouse relative to Base)
    float dx = static_cast<float>(mousePos.x) - origin.x;
    float dy = static_cast<float>(mousePos.y) - origin.y;

    // 2. Distance Calculation
    float dist = std::sqrt(dx*dx + dy*dy);

    // 3. Clamp (Prevent arm breaking)
    float maxReach = l1 + l2;
    if (dist > maxReach) {
        float scale = maxReach / dist;
        dx *= scale;
        dy *= scale;
        dist = maxReach;
    }

    // 4. Inverse Kinematics (Law of Cosines)
    // cos(theta2) = (x^2 + y^2 - l1^2 - l2^2) / (2 * l1 * l2)
    float cos_theta2 = (dx*dx + dy*dy - l1*l1 - l2*l2) / (2 * l1 * l2);

    // Floating point safety clamp (-1.0 to 1.0)
    cos_theta2 = std::max(-1.0f, std::min(1.0f, cos_theta2));

    theta2 = std::acos(cos_theta2);

    // 5. Calculate Shoulder (theta1)
    float k1 = l1 + l2 * std::cos(theta2);
    float k2 = l2 * std::sin(theta2);

    theta1 = std::atan2(dy, dx) - std::atan2(k2, k1);
}

void Arm::draw(sf::RenderWindow& window) {
    // Forward Kinematics for drawing points
    // Joint 1 (Base) is 'origin'

    // Joint 2 (Elbow)
    float x1 = origin.x + l1 * std::cos(theta1);
    float y1 = origin.y + l1 * std::sin(theta1);

    // End Effector (Hand)
    float x2 = x1 + l2 * std::cos(theta1 + theta2);
    float y2 = y1 + l2 * std::sin(theta1 + theta2);

    // SFML VertexArray for drawing lines (High Performance)
    sf::Vertex line1[] = {
        sf::Vertex(origin, sf::Color::White),
        sf::Vertex(sf::Vector2f(x1, y1), sf::Color::White)
    };

    sf::Vertex line2[] = {
        sf::Vertex(sf::Vector2f(x1, y1), sf::Color::White),
        sf::Vertex(sf::Vector2f(x2, y2), sf::Color::White)
    };

    window.draw(line1, 2, sf::Lines);
    window.draw(line2, 2, sf::Lines);

    // Optional: Draw Joints as circles
    sf::CircleShape joint(5);
    joint.setFillColor(sf::Color::Red);
    
    // Draw Elbow
    joint.setPosition(x1 - 5, y1 - 5);
    window.draw(joint);

    // Draw Hand
    joint.setPosition(x2 - 5, y2 - 5);
    window.draw(joint);
}