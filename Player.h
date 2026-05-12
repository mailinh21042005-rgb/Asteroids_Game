// Player.h
#pragma once
#include "Entity.h"
#include "GameConfig.h"
#include <SFML/Graphics.hpp>

class player : public Entity
{
public:
    bool thrust = false;

    // spin
    float spinSpeed = 0.f;
    bool exitingWhiteHole = false;

    // respawn protection
    bool invulnerable = false;
    sf::Clock invulClock;
    float invulDuration = 2.5f;   // seconds

    bool visible = true;          // flicker control

    player();
    void update() override;
    void draw(sf::RenderWindow& app) override;
};
