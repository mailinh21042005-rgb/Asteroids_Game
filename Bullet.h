// Bullet.h
#pragma once
#include "Entity.h"
#include "GameConfig.h"

class bullet : public Entity
{
public:
    bullet();
    void update() override;
};
