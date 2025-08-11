#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

// Calculates new velocity after air resistance effect
// velocity_px: current velocity in pixels per second (positive downward)
// mass: mass in kg
// radius_m: ball radius in meters
// dt: elapsed time in seconds
// pixelsToMeters: conversion factor from pixels to meters
float applyAirResistance(float velocity_px, float mass, float radius_m, float dt, float pixelsToMeters) {
    const float airDensity = 1.225f;          // Air density (kg/m^3)
    const float dragCoefficient = 0.47f;      // Drag coefficient for a sphere
    const float crossSectionalArea = 3.14159f * radius_m * radius_m; // Frontal area (m^2)

    // Convert velocity to m/s
    float velocity_m = velocity_px * pixelsToMeters;

    // Calculate drag force (N)
    float dragForce = 0.5f * airDensity * velocity_m * velocity_m * dragCoefficient * crossSectionalArea;

    // Drag acceleration (m/s^2)
    float dragAccel_m = dragForce / mass;

    // Convert acceleration back to pixels/s^2
    float dragAccel_px = dragAccel_m / pixelsToMeters;

    // Apply drag acceleration opposite to velocity direction
    if (velocity_px > 0)
        velocity_px -= dragAccel_px * dt;
    else if (velocity_px < 0)
        velocity_px += dragAccel_px * dt;

    return velocity_px;
}

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 1000
#define COLOR_RED 255, 0, 0
#define COLOR_SKY 130, 200, 229

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Physics Simulation: Free Fall of a Ball");

    // Ball setup
    float mass = 0.45f;                // kg (standard football mass)
    float radius_m = 0.11f;            // meters (standard football radius)
    float pixelsToMeters = 1.f / 50.f; // scale: 50 pixels = 1 meter

    // Note: SFML CircleShape radius is in pixels, so convert meters to pixels
    sf::CircleShape ball(radius_m * 50.f);
    ball.setPosition(sf::Vector2f(400, radius_m * 50.f)); // start near top
    ball.setFillColor(sf::Color(COLOR_RED));
    ball.setOutlineThickness(10.f);
    ball.setOutlineColor(sf::Color(180, 0, 0));
    ball.setOrigin(sf::Vector2f(radius_m * 50.f, radius_m * 50.f)); // center origin

    // Physics parameters
    float gravity = 981.f; // pixels per second squared
    float velocity = 0.f;  // pixels per second

    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Time elapsed since last frame
        float dt = clock.restart().asSeconds();

        // Apply air resistance to velocity
        velocity = applyAirResistance(velocity, mass, radius_m, dt, pixelsToMeters);

        // Apply gravity acceleration
        velocity += gravity * dt;

        // Update ball position
        sf::Vector2f pos = ball.getPosition();
        pos.y += velocity * dt;

        // Simple ground collision with bounce
        if (pos.y + radius_m * 50.f > WINDOW_HEIGHT) {
            pos.y = WINDOW_HEIGHT - (radius_m * 50.f);
            velocity = -velocity * 0.7f; // bounce with 30% energy loss
        }

        ball.setPosition(pos);

        window.clear(sf::Color(COLOR_SKY));
        window.draw(ball);
        window.display();
    }
}
