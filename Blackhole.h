// Blackhole.h
#pragma once
#include "Entity.h"

class blackhole : public Entity
{
public:
    sf::Clock lifeClock;
    float lifetime = 2.5f;

    blackhole();
    void update() override;
};
