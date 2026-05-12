// Asteroid.h
#pragma once
#include "Entity.h"
#include "GameConfig.h"

class asteroid : public Entity
{
public:
    asteroid();
    void update() override;
};
