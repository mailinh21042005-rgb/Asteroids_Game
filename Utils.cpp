#include "Utils.h"
#include "Entity.h"
#include "Blackhole.h"
#include "Player.h"
#include <cstdlib>

// --------------------------------------------------
// Circle collision test
// --------------------------------------------------
bool isCollide(Entity* a, Entity* b)
{
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float r  = a->R + b->R;

    return (dx * dx + dy * dy) < (r * r);
}

// --------------------------------------------------
// Detect if position is in the border zone
// --------------------------------------------------
bool isPlayerNearEdge(Entity* p, float margin)
{
    return (p->x < margin || p->x > W - margin ||
            p->y < margin || p->y > H - margin);
}

// --------------------------------------------------
// Random teleport position in safe zone
// --------------------------------------------------
sf::Vector2f randomSafePosition()
{
    float x = DANGER_BORDER +
              static_cast<float>(rand()) / RAND_MAX *
              (W - 2 * DANGER_BORDER);

    float y = DANGER_BORDER +
              static_cast<float>(rand()) / RAND_MAX *
              (H - 2 * DANGER_BORDER);

    return sf::Vector2f(x, y);
}
// --------------------------------------------------
// Draw blackhole eclipse (no sprite)
// --------------------------------------------------
void drawBlackholeEclipse(sf::RenderWindow& app, blackhole* bh)
{
    sf::CircleShape eclipse(bh->R);
    eclipse.setOrigin(bh->R, bh->R);
    eclipse.setPosition(bh->x, bh->y);
    eclipse.setFillColor(sf::Color::Black);

    app.draw(eclipse);
}