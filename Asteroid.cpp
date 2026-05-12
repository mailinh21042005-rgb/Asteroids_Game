// Asteroid.cpp
#include "Asteroid.h"
#include <cstdlib>

asteroid::asteroid()
{
    name = "asteroid";
}

void asteroid::update()
{
    x += dx;
    y += dy;

    float margin = R + 20;
    if (x < -margin || x > W + margin || y < -margin || y > H + margin) life = false;
}
