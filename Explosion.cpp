#include "Explosion.h"

Explosion::Explosion(Animation& a, float X, float Y)
{
    name = "explosion";
    settings(a, X, Y);
}

void Explosion::update()
{
    // explosion does not move
}
