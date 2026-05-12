#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Animation.h"

class Entity
{
public:
    float x = 0, y = 0;
    float dx = 0, dy = 0;
    float R = 1;
    float angle = 0;
    bool life = true;
    std::string name;
    Animation anim;

    virtual ~Entity() = default;
    Entity ();
    void settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1);
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& app);
};