#include "EdgePunishSystem.h"
#include "Entity.h"
#include "Player.h"
#include "SpawnSystem.h"
#include "Utils.h"
#include "Sound.h"

void EdgePunishSystem::spawnAllPunish(std::list<Entity*>& entities,
                                     player* p,
                                     SpawnSystem& spawner)
{
    sf::Vector2f spawnPoints[5] =
    {
        {W / 4.f, 0.f},
        {W / 2.f, 0.f},
        {3 * W / 4.f, 0.f},
        {0.f, H / 2.f},
        {W * 1.f, H / 2.f}
    };

    for (int i = 0; i < 5; i++)
        spawner.spawnPunish(entities, spawnPoints[i], p);
}

void EdgePunishSystem::update(std::list<Entity*>& entities,
                              player* p,
                              SpawnSystem& spawner,
                              SoundManager& sound)
{
    if (isPlayerNearEdge(p))
    {
        if (!inEdge)
        {
            inEdge = true;
            timer.restart();
            firstSpawnDone = false;

            if (!soundPlayed)
            {
                sound.playWarning();
                soundPlayed = true;
            }
        }
        else
        {
            float t = timer.getElapsedTime().asSeconds();
            if (!firstSpawnDone && t >= initialDelay)
            {
                spawnAllPunish(entities, p, spawner);
                firstSpawnDone = true;
                timer.restart();
            }
            else if (firstSpawnDone && t >= repeatDelay)
            {
                spawnAllPunish(entities, p, spawner);
                timer.restart();
            }
        }
    }
    else
    {
        inEdge = false;
        timer.restart();
        firstSpawnDone = false;
        if (soundPlayed)
        {
            sound.stopWarning();
            soundPlayed = false;
        }
    }
}

bool EdgePunishSystem::isWarningActive() const
{
    return inEdge && !firstSpawnDone;
}

float EdgePunishSystem::getWarningTimeLeft() const
{
    return initialDelay - timer.getElapsedTime().asSeconds();
}