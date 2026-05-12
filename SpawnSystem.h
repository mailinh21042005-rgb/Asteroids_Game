#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class Entity;
class asteroid;
class player;
class Animation;

extern const int W;
extern const int H;

class SpawnSystem
{
private:
    sf::Vector2f spawnPoints[5] = {
        { static_cast<float>(W) / 4.f, 0.f },
        { static_cast<float>(W) / 2.f, 0.f },
        { static_cast<float>(3 * W) / 4.f, 0.f },
        { 0.f, static_cast<float>(H) / 2.f },
        { static_cast<float>(W), static_cast<float>(H) / 2.f }
    };

    Animation& rockBig;
    Animation& rockSmall;

    float radius;
    float speedMin, speedMax;

    struct FanBullet
    {
        sf::Vector2f pos;
        float angle, speed, radius;
    };

    std::list<FanBullet> fanQueue;
    sf::Clock fanClock;
    float fanDelay = 0.2f;

    void chooseType();
    void createAsteroid(sf::Vector2f pos, float angle,
                        std::list<Entity*>& entities,
                        float speed, float r);

public:
    SpawnSystem(Animation& big, Animation& small);

    void spawnSingle(std::list<Entity*>& entities);
    void spawnFan(std::list<Entity*>& entities);
    void spawnPunish(std::list<Entity*>& entities, sf::Vector2f pos, player* p);
    void updateFan(std::list<Entity*>& entities);
};
