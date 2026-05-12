#include "Whitehole.h"
#include "GameConfig.h"

Whitehole::Whitehole(float X, float Y)
{
    name = "whitehole";
    x = X;
    y = Y;
    dx = dy = 0;
    R = HOLE_RADIUS;
    life = true;
}

void Whitehole::update()
{
    if (lifeClock.getElapsedTime().asSeconds() > lifetime)
        life = false;
}

void Whitehole::draw(sf::RenderWindow& app)
{
    sf::CircleShape hole(R);
    hole.setOrigin(R, R);
    hole.setPosition(x, y);
    hole.setFillColor(sf::Color::Black);  // ← black, same as blackhole

    app.draw(hole);
}

