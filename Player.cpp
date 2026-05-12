#include "Player.h"
#include <cmath>

player::player()
{
    name = "player";
}

void player::update()
{
    // ------------------ INVULNERABILITY ------------------
    if (invulnerable)
    {
        float t = invulClock.getElapsedTime().asSeconds();

        // flicker at 10 Hz
        visible = (static_cast<int>(t * 10.f) % 2 == 0);

        if (t >= invulDuration)
        {
            invulnerable = false;
            visible = true;
        }
    }
    else
    {
        visible = true;
    }

    // ------------------ ROTATION ------------------
    angle += spinSpeed;

    if (exitingWhiteHole)
    {
        spinSpeed *= 0.90f;   // strong damping after white hole

        if (spinSpeed < 5.f)
            exitingWhiteHole = false;
    }
    else
    {
        spinSpeed *= 0.98f;   // gentle natural damping
    }

    if (std::abs(spinSpeed) < 0.05f)
        spinSpeed = 0.f;

    // ------------------ MOVEMENT ------------------
    if (thrust)
    {
        dx += std::cos(angle * DEGTORAD) * 0.2f;
        dy += std::sin(angle * DEGTORAD) * 0.2f;
    }
    else
    {
        dx *= 0.99f;
        dy *= 0.99f;
    }

    float speed = std::sqrt(dx * dx + dy * dy);
    const float maxSpeed = 9.0f;

    if (speed > maxSpeed)
    {
        dx *= maxSpeed / speed;
        dy *= maxSpeed / speed;
    }

    x += dx;
    y += dy;

    if (x > W) x = 0;
    if (x < 0) x = W;
    if (y > H) y = 0;
    if (y < 0) y = H;
}

void player::draw(sf::RenderWindow& app)
{
    if (!visible) return;

    anim.sprite.setPosition(x, y);
    anim.sprite.setRotation(angle + 90);
    app.draw(anim.sprite);
}
