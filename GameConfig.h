#pragma once
#include <SFML/Graphics.hpp>

inline const float SHOOT_COOLDOWN = 0.2f;
inline const int W = 1200;
inline const int H = 800;
inline const int DANGER_BORDER = 100;

inline const float DEGTORAD = 0.017453f;
inline const float BLACKHOLE_WARNING_TIME = 3.0f;
inline const float SAFE_DURATION = 30.f;

constexpr float HOLE_RADIUS = 30.f;

// -------------------- SOUND FLAGS --------------------
extern bool blackholeSoundPlayed;

// -------------------- BLACKHOLE STATE --------------------
enum class blackholeState
{
    SAFE,
    DANGER,
    COOLDOWN
};
