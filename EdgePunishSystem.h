#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Sound.h"

using namespace sf;

class Entity;
class player;
class SpawnSystem;

extern const int W;
extern const int H;

class EdgePunishSystem
{
private:
    sf::Clock timer;
    bool inEdge = false;
    float initialDelay = 3.f;
    float repeatDelay = 1.f;
    bool firstSpawnDone = false;
    bool soundPlayed = false;

    void spawnAllPunish(std::list<Entity*>& entities,
                        player* p,
                        SpawnSystem& spawner);

public:
    void update(std::list<Entity*>& entities,
                player* p,
                SpawnSystem& spawner,
                SoundManager& sound);  
    bool isWarningActive() const;
    float getWarningTimeLeft() const;
};
