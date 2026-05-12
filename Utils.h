#pragma once
#include <SFML/Graphics.hpp>
#include "GameConfig.h"
#include "Entity.h"
#include "Player.h"
#include "Blackhole.h"

bool isCollide(class Entity* a, class Entity* b);
bool isPlayerNearEdge(class Entity* p, float margin = 100.f);
sf::Vector2f randomSafePosition();
void drawBlackholeEclipse(sf::RenderWindow& app, class blackhole* bh);
