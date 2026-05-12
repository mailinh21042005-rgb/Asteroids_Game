@echo off
echo Dang bien dich game... (vui long doi)

g++ ^
main.cpp ^
Animation.cpp ^
Asteroid.cpp ^
Blackhole.cpp ^
Whitehole.cpp ^
Bullet.cpp ^
Entity.cpp ^
Explosion.cpp ^
Player.cpp ^
Utils.cpp ^
Sound.cpp ^
EdgePunishSystem.cpp ^
SpawnSystem.cpp ^
-o game ^
-I SFML/include ^
-L SFML/lib ^
-lsfml-graphics ^
-lsfml-window ^
-lsfml-system ^
-lsfml-audio

if %errorlevel% neq 0 (
    echo.
    echo ===== BUILD THAT BAI =====
) else (
    echo.
    echo ===== BUILD THANH CONG =====
    echo Dang chay game...
    game.exe
)

pause
