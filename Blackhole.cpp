// Blackhole.cpp
#include "Blackhole.h"
#include "GameConfig.h"

blackhole::blackhole()
{
    name = "blackhole";
    dx = dy = 0;
    R = HOLE_RADIUS;
}


void blackhole::update()
{
    if (lifeClock.getElapsedTime().asSeconds() > lifetime)
        life = false;
}
