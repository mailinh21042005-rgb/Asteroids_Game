#include "SpawnSystem.h"
#include "Entity.h"
#include "asteroid.h"
#include "Player.h"
#include "Animation.h"
#include <cstdlib>
#include <cmath>

SpawnSystem::SpawnSystem(Animation& big, Animation& small)
    : rockBig(big), rockSmall(small) {}
// choose size of asteroid
void SpawnSystem::chooseType()
{
    int type = rand() % 2;
    if (type == 1)
    {
        radius = 25;
        speedMin = 2.5f;
        speedMax = 4.f;
    }
    else
    {
        radius = 15;
        speedMin = 4.f;
        speedMax = 6.f;
    }
}
// create asteroid
void SpawnSystem::createAsteroid(sf::Vector2f pos, float angle,
                                 std::list<Entity*>& entities,
                                 float speed, float r)
{
    asteroid* a = new asteroid();

    if (r == 15)
        a->settings(rockSmall, pos.x, pos.y, angle, r);
    else
        a->settings(rockBig, pos.x, pos.y, angle, r);

    a->dx = cos(angle * DEGTORAD) * speed;
    a->dy = sin(angle * DEGTORAD) * speed;

    entities.push_back(a);
}
// spawn single asteroid
void SpawnSystem::spawnSingle(std::list<Entity*>& entities)
{
    chooseType();
    int id = rand() % 5;
    float angle;

    switch (id)
    {
    case 0:
        angle = rand() % 140 + 20;
        break;
    case 1:
        angle = rand() % 140 + 20;
        break;
    case 2:
        angle = rand() % 140 + 20;
        break;
    case 3:
        angle = rand() % 140 + 290;
        break;
    case 4:
        angle = rand() % 140 + 110;
        break;
    }

    float speed = speedMin + rand() % int(speedMax - speedMin + 1);
    createAsteroid(spawnPoints[id], angle, entities, speed, radius);
}
// spawn fan of asteroids
void SpawnSystem::spawnFan(std::list<Entity*>& entities)
{
    chooseType(); // choose size
    int id = rand() % 5; // choose position
    int count = (rand() % 4) + 3; // choose quantity
    float baseAngle;

    switch (id)
    {
    case 0:
        baseAngle = rand() % 140 + 20;
        break;
    case 1:
        baseAngle = rand() % 140 + 20;
        break;
    case 2:
        baseAngle = rand() % 140 + 20;
        break;
    case 3:
        baseAngle = rand() % 140 + 290;
        break;
    case 4:
        baseAngle = rand() % 140 + 110;
        break;
    }

    float speed = speedMin + rand() % int(speedMax - speedMin + 1);
    float startAngle = baseAngle - 5 * (count - 1);
    float chosenRadius = radius;

    for (int i = 0; i < count; i++)
    {
        FanBullet fb;
        fb.pos = spawnPoints[id];
        fb.angle = startAngle + 10 * i;
        fb.speed = speed;
        fb.radius = chosenRadius;
        fanQueue.push_back(fb);
    }

    fanClock.restart();
}
// spawn punish asteroid aimed at player
void SpawnSystem::spawnPunish(std::list<Entity*>& entities, sf::Vector2f pos, player* p)
{
    float radius = 40.f;
    float speed = 10.f;

    float dx = p->x - pos.x;
    float dy = p->y - pos.y;
    float angle = atan2(dy, dx) / DEGTORAD;

    asteroid* a = new asteroid();
    a->settings(rockBig, pos.x, pos.y, angle, radius);

    float scale = radius / 25.f;
    a->anim.sprite.setScale(scale, scale);

    a->dx = cos(angle * DEGTORAD) * speed;
    a->dy = sin(angle * DEGTORAD) * speed;

    entities.push_back(a);
}
// update fan spawning
void SpawnSystem::updateFan(std::list<Entity*>& entities)
{
    if (fanQueue.empty()) return;

    if (fanClock.getElapsedTime().asSeconds() >= fanDelay)
    {
        FanBullet fb = fanQueue.front();
        fanQueue.pop_front();

        createAsteroid(fb.pos, fb.angle, entities, fb.speed, fb.radius);
        fanClock.restart();
    }
}