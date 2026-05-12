#pragma once
#include "Entity.h"

class Whitehole : public Entity
{
public:
    sf::Clock lifeClock;
    float lifetime = 0.6f;

    Whitehole(float X, float Y);

    void update() override;
    void draw(sf::RenderWindow& app);
};
