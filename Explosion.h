#pragma once
#include "Entity.h"

class Explosion : public Entity
{
public:
    Explosion(Animation& anim, float x, float y);

    void update() override;
};
