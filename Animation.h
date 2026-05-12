#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
public:
    float Frame = 0;
    float speed = 0;
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;

    Animation();
    Animation(sf::Texture& t, int x, int y, int w, int h, int count, float Speed);

    void update();
    bool isEnd() const;
};
