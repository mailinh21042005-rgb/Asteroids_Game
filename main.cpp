#include <SFML/Graphics.hpp>

#include <list>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

#include "GameConfig.h"
#include "Animation.h"
#include "Entity.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include "Blackhole.h"
#include "Whitehole.h"
#include "Explosion.h"
#include "Utils.h"
#include "Sound.h"
#include "SpawnSystem.h"
#include "EdgePunishSystem.h"

using namespace sf;
enum GameState { MENU_CHINH, DANG_CHOI, PAUSE, SETTING };
int main()
{
    // LOAD BACKGROUND MUSIC AND SOUND EFFECTS
    sf::Clock warningClock;
    bool warningActive = false;
    bool blackholeSoundPlayed = false;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    SoundManager sound;
    sound.playMenuMusic();
    // --------------------------------------------------

    // CREATE WINDOW
    RenderWindow app(VideoMode(W, H), "Asteroids!");
    app.setFramerateLimit(60);
    // --------------------------------------------------

    // --------------------------------------------------
    // LOAD TEXTURES
    // --------------------------------------------------
    Texture t1, t2, t3, t4, t5, t6, t7,
            t1Player, t2Player, tExit, tSetting, tLittleBao,
            tPause, tRetry, tContinue, tExitPause;
    // Textures for orginal code
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_blue.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");

    // Textures for main menu
    t1Player.loadFromFile("images/menu/1_player.png");
    t2Player.loadFromFile("images/menu/2_player.png");
    tExit.loadFromFile("images/menu/exit.png");
    tSetting.loadFromFile("images/menu/setting.png");
    tLittleBao.loadFromFile("images/menu/littlebao.png");

    // Textures for pause menu
    tPause.loadFromFile("images/menu/PauseBG.png");
    tRetry.loadFromFile("images/menu/retry.png");
    tContinue.loadFromFile("images/menu/continue.png");
    tExitPause.loadFromFile("images/menu/exit.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    Sprite background(t2),
           s1Player(t1Player), 
           s2Player(t2Player), 
           sExit(tExit), 
           sSetting(tSetting), 
           sBao(tLittleBao),
           sPause(tPause),
           sRetry(tRetry),
           sContinue(tContinue),
           sExitPause(tExitPause);

    // --------------------------------------------------
    // ANIMATIONS
    // --------------------------------------------------
    Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5f);
    Animation sRock(t4, 0, 0, 64, 64, 16, 0.2f);
    Animation sRockSmall(t6, 0, 0, 64, 64, 16, 0.2f);
    Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8f);
    Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
    Animation sPlayerGo(t1, 40, 40, 40, 40, 1, 0);
    Animation sExplosionShip(t7, 0, 0, 192, 192, 64, 0.5f);

    // --------------------------------------------------
    // OPTIONS
    // --------------------------------------------------
    GameState state = MENU_CHINH;
    GameState prevState = MENU_CHINH;
    GameState settingFromState = MENU_CHINH;

    int menuIdx = 0; // Options in main menu
    int pauseIdx = 0; // Options in pause menu
    int settingIdx = 0; // Options in setting menu

    // --------------------------------------------------
    // ENTITY LIST
    // --------------------------------------------------
    std::list<Entity*> entities;
    player* p = new player();
    
    // Reset function for Retry option
    auto resetGame = [&]() 
    {
        for (auto it = entities.begin(); it != entities.end(); )
        {
            if (*it == p)   
            {
                ++it;
            }
            else
            {
                delete *it;
                it = entities.erase(it);
            }
        }
        // reset player
        p->settings(sPlayer, W / 2, H / 2, 0, 20);
        p->dx = p->dy = 0;
        p->spinSpeed = 0.f;
        p->thrust = false;
        p->exitingWhiteHole = false;
        p->invulnerable = false;

        if (std::find(entities.begin(), entities.end(), p) == entities.end())
            entities.push_back(p);
    };

    resetGame();

    // Spawner
    SpawnSystem spawner(sRock, sRockSmall);
    EdgePunishSystem edgePunish;   

    // --------------------------------------------------
    // BLACKHOLE STATE
    // --------------------------------------------------
    blackholeState bhState = blackholeState::SAFE;
    sf::Clock blackholeClock;
    bool blackholeTriggered = false;
    float triggerTime = 0.f;
    bool playerCaptured = false;
    sf::Clock captureClock;

    // --------------------------------------------------
    // WHITEHOLE STATE
    // --------------------------------------------------
    bool playerReappearing = false;
    sf::Clock reappearClock;
    // --------------------------------------------------

    // MAIN LOOP
    // --------------------------------------------------
    sf::Clock shootClock;
    while (app.isOpen())
    {
        // -------------------- SOUND ---------------------
        if (state != prevState)
        
            if (state == MENU_CHINH)
                sound.playMenuMusic();
            else if (state == DANG_CHOI)
                sound.playGameMusic();

            prevState = state;
        }
        // -------------------- EVENTS --------------------
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
        // -------------------- HANDLE KEY PRESSES --------------------
            if (event.type == Event::KeyPressed)
            {
                // Logic for menus
                if (state == MENU_CHINH)
                { 
                    if (event.key.code == Keyboard::Up)
                    {
                        menuIdx = (menuIdx - 1 + 4) % 4;
                        sound.playEnter();
                    }
                    if (event.key.code == Keyboard::Down)
                    {
                        menuIdx = (menuIdx + 1) % 4;
                        sound.playEnter();
                    }
                    if (event.key.code == Keyboard::Return)
                    {
                        sound.playEnter();
                        if (menuIdx == 0)
                            state = DANG_CHOI;
                        if (menuIdx == 1)
                        { 
                            // Block 2 Players // }
                        }
                        if (menuIdx == 2)
                        {
                            settingFromState = MENU_CHINH;
                            state = SETTING;
                            sound.playEnter();          
                        }
                        if (menuIdx == 3)
                            app.close();
                    }
                }

                // Logic SETTING MENU
                else if (state == SETTING) 
                {
                    if (event.key.code == Keyboard::Up) {
                        settingIdx = (settingIdx - 1 + 2) % 2;
                        sound.playEnter();
                    }
                    if (event.key.code == Keyboard::Down) {
                        settingIdx = (settingIdx + 1) % 2;
                        sound.playEnter();
                    }

                    if (settingIdx == 0) {
                        if (event.key.code == Keyboard::Right) 
                        {
                            float vol = sound.getVolume() + 5.f;
                            if (sound.getVolume() >= 100.f){
                                sound.setVolume(100.f);
                            } 
                            else {
                                sound.setVolume(vol);
                            }
                            sound.playEnter();
                        }
                        else if (event.key.code == Keyboard::Left) {
                            float vol = sound.getVolume() - 5.f;
                            if (sound.getVolume() <= 0.f){
                                sound.setVolume(0.f);
                            } 
                            else {
                                sound.setVolume(vol);
                            }
                            sound.playEnter();
                        }
                    }

                    if (event.key.code == Keyboard::Return) {
                        if (settingIdx == 1) {
                            state = settingFromState; 
                            sound.playEnter();
                        }
                    }

                    // Nhấn ESC luôn luôn thoát về prevState để tránh bị kẹt
                    if (event.key.code == Keyboard::Escape) {
                        state = settingFromState;
                        sound.playEnter();
                    }
                }


                // Logic while playing (press ESC to Pause)
                else if (state == DANG_CHOI)
                {
                    if (event.key.code == Keyboard::Escape)
                    {
                        sound.playEnter(); // sound effect when pressing ESC
                        state = PAUSE;
                        sound.stopWarning();
                        sound.stopAlert();
                    }
                }

                // Logic for Pause menu
                else if (state == PAUSE)
                {
                    if (event.key.code == Keyboard::Up)
                    {
                        pauseIdx = (pauseIdx - 1 + 4) % 4;
                        sound.playEnter();
                    }
                    if (event.key.code == Keyboard::Down)
                    {
                        pauseIdx = (pauseIdx + 1) % 4;
                        sound.playEnter();
                    }
                    if (event.key.code == Keyboard::Return)
                    {
                        sound.playEnter();
                        if (pauseIdx == 0) // continue
                        {
                         state = DANG_CHOI;
                            if (warningActive)
                            {
                                sound.playAlert();
                            }
                        }
                        if (pauseIdx == 1)  // Retry
                        {
                            sound.stopAlert();
                            resetGame();
                            bhState = blackholeState::SAFE;
                            blackholeTriggered = false;
                            warningActive = false;
                            blackholeSoundPlayed = false;
                            blackholeClock.restart();
                            // delete old blackholes
                            for (auto it = entities.begin(); it != entities.end(); )
                            {
                                if ((*it)->name == "blackhole")
                                {
                                    delete *it;
                                    it = entities.erase(it);
                                }
                                else
                                {
                                    ++it;
                                }
                            }
                            // reset state
                            p->dx = 0;
                            p->dy = 0;
                            p->spinSpeed = 0.f;
                            p->thrust = false;
                            p->exitingWhiteHole = false;
                            playerCaptured = false;
                            state = DANG_CHOI;
                        }
                        if (pauseIdx == 2) // pause
                        { 
                            settingFromState = PAUSE;
                            state = SETTING;
                            sound.playEnter();
                        }
                        if (pauseIdx == 3) //exit
                        {
                            sound.stopAlert();
                            state = MENU_CHINH;
                            resetGame();
                            bhState = blackholeState::SAFE;
                            blackholeTriggered = false;
                            warningActive = false;
                            blackholeSoundPlayed = false;
                            blackholeClock.restart();
                            for (auto it = entities.begin(); it != entities.end(); )
                            {
                                if ((*it)->name == "blackhole")
                                {
                                    delete *it;
                                    it = entities.erase(it);
                                }
                                else
                                {
                                    ++it;
                                }
                            }
                            p->dx = 0;
                            p->dy = 0;
                            p->spinSpeed = 0.f;
                            p->thrust = false;
                            p->exitingWhiteHole = false;
                            playerCaptured = false;
                        } // Exit
                    }
                }
            }
                
            // Shoot bullet with cooldown
            if (event.type == Event::KeyReleased)
            {
                if (state == DANG_CHOI && event.key.code == Keyboard::Space && shootClock.getElapsedTime().asSeconds() >= SHOOT_COOLDOWN)
                {
                    bullet* b = new bullet();
                    b->settings(sBullet, p->x, p->y, p->angle, 10);
                    entities.push_back(b);

                    sound.playShoot();
                    shootClock.restart();
                }
            }
        }

        // -------------------- INPUT --------------------
        if (state == DANG_CHOI)
        {
            if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle += 3;
            if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle -= 3;
            if (!playerCaptured && Keyboard::isKeyPressed(Keyboard::Up))
                p->thrust = true;
            else
                p->thrust = false;

            // -------------------- BLACKHOLE STATE --------------------
            float elapsed = blackholeClock.getElapsedTime().asSeconds();

            switch (bhState)
            {
            case blackholeState::SAFE:
                warningActive= false;
                blackholeSoundPlayed = false;
                if (elapsed >= SAFE_DURATION)
                {
                    bhState = blackholeState::DANGER;
                    blackholeClock.restart();
                    blackholeTriggered = false;
                    const float DANGER_DURATION = 15.f;
                    triggerTime = BLACKHOLE_WARNING_TIME + static_cast<float>(rand()) / RAND_MAX * (DANGER_DURATION - BLACKHOLE_WARNING_TIME);
                }
                break;

            case blackholeState::DANGER:
                if (!blackholeTriggered && elapsed >= triggerTime && !warningActive)
                {
                    blackhole* bh = new blackhole();
                    bh->x = p->x;
                    bh->y = p->y;
                    entities.push_back(bh);

                if (!blackholeSoundPlayed)
                {
                    sound.playBlackhole();
                    blackholeSoundPlayed = true;
                }
                    
                    blackholeTriggered = true;
                    playerCaptured = false;
                }

                if (elapsed >= 15.f)
                {
                    bhState = blackholeState::SAFE;
                    blackholeClock.restart();
                }
                break;

            default:
                break;
            }

            // -------------------- FORCED CAPTURE --------------------
            if (bhState == blackholeState::DANGER && blackholeTriggered)
            {
                for (auto e : entities)
                {
                    if (e->name == "blackhole")
                    {
                        float dx = e->x - p->x;
                        float dy = e->y - p->y;
                        p->dx += dx * 0.02f;
                        p->dy += dy * 0.02f;
                        float maxSpeed = 8.f;
                        p->dx = std::clamp(p->dx, -maxSpeed, maxSpeed);
                        p->dy = std::clamp(p->dy, -maxSpeed, maxSpeed);

                        p->dx *= 0.95f;
                        p->dy *= 0.95f;

                        if (!playerCaptured)
                        {
                            playerCaptured = true;
                            if (playerCaptured)
                            {
                                // ramp up spin speed (sucking effect)
                                if (p->spinSpeed < 1.f) p->spinSpeed = 1.f;
                                p->spinSpeed *= 10.0f;        
                                if (p->spinSpeed > 120.f) p->spinSpeed = 120.f;
                            }
                            captureClock.restart();
                        }
                    }
                }
            }

            // -------------------- TELEPORT --------------------
            if (playerCaptured &&
                captureClock.getElapsedTime().asSeconds() > 1.2f)
            {
                sf::Vector2f pos = randomSafePosition();

                // spawn white hole FIRST
                Whitehole* wh = new Whitehole(pos.x, pos.y);
                entities.push_back(wh);
                sound.playWhitehole(); 

                // hide player temporarily
                p->x = -1000;
                p->y = -1000;
                p->dx = p->dy = 0;
                p->spinSpeed = 0.f;

                playerCaptured = false;
                playerReappearing = true;
                reappearClock.restart();

                blackholeTriggered = false;
                bhState = blackholeState::SAFE;
                blackholeClock.restart();
            }

            // -------------------- UPDATE --------------------
            if (state == DANG_CHOI)
            {
                for (auto it = entities.begin(); it != entities.end(); )
                {
                    Entity* e = *it;
                    e->update();
                    e->anim.update();

                    if (!e->life)
                    {
                        it = entities.erase(it);
                        delete e;
                    }
                    else
                        ++it;
                 }
            }
            
            // -------------------- PLAYER EMERGE FROM WHITE HOLE --------------------

            if (playerReappearing &&
                reappearClock.getElapsedTime().asSeconds() > 0.3f)
            {
                // find white hole
                for (auto e : entities)
                {
                    if (e->name == "whitehole")
                    {
                        p->x = e->x;
                        p->y = e->y;

                        // shoot outward
                        float angleOut = static_cast<float>(rand() % 360);
                        constexpr float WHITEHOLE_EXIT_SPEED = 2.5f;
                        p->dx = std::cos(angleOut * DEGTORAD) * WHITEHOLE_EXIT_SPEED;
                        p->dy = std::sin(angleOut * DEGTORAD) * WHITEHOLE_EXIT_SPEED;

                        // strong spin
                        p->spinSpeed = 80.f;
                        p->exitingWhiteHole = true;

                        p->invulnerable = true;
                        p->invulClock.restart();

                        break;
                    }
                }

                playerReappearing = false;
            }
            // -------------------- COLLISIONS --------------------
            for (auto a : entities)
                for (auto b : entities)
                {
                    if (a->name == "asteroid" && b->name == "bullet")
                    {
                        if (!a->life || !b->life) continue;

                        if (isCollide(a, b))
                        {
                            a->life = false;
                            b->life = false;

                            Explosion* ex = new Explosion(sExplosion, a->x, a->y);
                            entities.push_back(ex);
                            sound.playExplosion();

                            if (a->R > 15)
                            {
                                for (int i = 0; i < 2; i++)
                                {
                                    asteroid* s = new asteroid();
                                    s->settings(
                                        sRockSmall,
                                        a->x,
                                        a->y,
                                        rand() % 360,
                                        15
                                    );               
                                    float angleRad = (rand() % 360) * DEGTORAD;
                                    float speed = static_cast<float>(rand() % 3 + 2);
                                    s->dx = std::cos(angleRad) * speed;
                                    s->dy = std::sin(angleRad) * speed;  

                                    entities.push_back(s);
                                }
                            }
                        }
                    }

                    if (a->name == "player" && b->name == "asteroid")
                    {
                        player* pl = static_cast<player*>(a);

                        if (pl->invulnerable) continue;

                        if (isCollide(a, b))
                        {
                            b->life = false;

                            Explosion* ex = new Explosion(sExplosionShip, a->x, a->y);
                            entities.push_back(ex);
                            sound.playDestroyed();
                            
                            pl->settings(sPlayer, W / 2, H / 2, 0, 20);
                            pl->dx = pl->dy = 0;
                            // Gameover logic can be added here

                            // activate respawn protection
                            pl->invulnerable = true;
                            pl->invulClock.restart();
                        }
                    }
                }

            // cleanup explosions
            for (auto e : entities)
                if (e->name == "explosion" && e->anim.isEnd())
                    e->life = false;
            
            // update asteroid spawner
            int r = rand() % 100;
            if (r == 0) spawner.spawnSingle(entities);
            else if (r == 1) spawner.spawnFan(entities);
            spawner.updateFan(entities);
            if (!playerReappearing && !playerCaptured) 
            {
                edgePunish.update(entities, p, spawner, sound);
            }
        }

        // -------------------- DRAW --------------------
        app.clear();
        app.draw(background);

        if (state == MENU_CHINH)
        {
            float mX = 150.f, mY = 220.f, sp = 120.f;
            // Draw menu options
            s1Player.setColor(Color(100, 100, 100)); 
            s2Player.setColor(Color(100, 100, 100));  
            sSetting.setColor(Color(100, 100, 100)); 
            sExit.setColor(Color(100, 100, 100));    

            float buttonScale = 0.6f; 
            s1Player.setScale(buttonScale, buttonScale);
            s2Player.setScale(buttonScale, buttonScale);
            sSetting.setScale(buttonScale, buttonScale);
            sExit.setScale(buttonScale, buttonScale);
            sBao.setScale(0.55f, 0.55f);  

            s1Player.setPosition(mX, mY);
            s2Player.setPosition(mX, mY + sp);
            sSetting.setPosition(mX, mY + sp * 2);
            sExit.setPosition(mX, mY + sp * 3.2f);
            sBao.setPosition(mX + 220.0f, mY - 80.0f);

            if (menuIdx == 0) 
            { 
                s1Player.setColor(Color::White); 
                s1Player.setPosition(mX + 30, mY); 
            }
            
            if (menuIdx == 1) 
            { 
                s2Player.setColor(Color::White); 
                s2Player.setPosition(mX + 30, mY + sp); 
            }
            
            if (menuIdx == 2) 
            { 
                sSetting.setColor(Color::White); 
                sSetting.setPosition(mX + 30, mY + sp * 2); 
            }
            
            if (menuIdx == 3) 
            { 
                sExit.setColor(Color::White);    
                sExit.setScale(0.7f, 0.7f);    
                sExit.setPosition(mX + 30, mY + sp * 3.2f); 
            } 

            app.draw(s1Player); 
            app.draw(s2Player); 
            app.draw(sSetting); 
            app.draw(sExit); 
            app.draw(sBao);
      }
      else if (state == SETTING)
        {
            RectangleShape overlay(Vector2f(W, H));
            overlay.setFillColor(Color(0, 0, 0, 200));
            app.draw(overlay);

            sSetting.setColor(Color::White);
            sSetting.setPosition(W / 2 - 100, H / 2 - 200);
            app.draw(sSetting);

            // Thanh Volume Background
            RectangleShape barBg(Vector2f(400.f, 30.f));
            barBg.setFillColor(Color(50, 50, 50));
            barBg.setOutlineThickness(2);
            barBg.setPosition(W / 2 - 200, H / 2);
            app.draw(barBg);

            // Thanh Volume Fill
            if (settingIdx == 0) {
                RectangleShape barFill(Vector2f(sound.getVolume() * 4.f, 30.f));
                barFill.setFillColor(Color::Cyan);
                barFill.setPosition(W / 2 - 200, H / 2);
                app.draw(barFill);
            }
            else {
                RectangleShape barFill(Vector2f(sound.getVolume() * 4.f, 30.f));
                barFill.setFillColor(Color::White);
                barFill.setPosition(W / 2 - 200, H / 2);
                app.draw(barFill);
            }
            
            //=====================
            sExitPause.setPosition(W / 2 - 80, H / 2 + 150);

            if (settingIdx == 1) {
                sExitPause.setColor(Color::White);
                sExitPause.setScale(0.7f, 0.7f);
            } else {
                sExitPause.setColor(Color(100, 100, 100)); // Màu tối khi không chọn
                sExitPause.setScale(0.6f, 0.6f);
            }
            app.draw(sExitPause);
            // sExitPause.setColor(Color::White);
            // 
            //app.draw(sExitPause);
        }
      else 
      {
        // black hole (background effect)
        for (auto e : entities)
            if (e->name == "blackhole")
                drawBlackholeEclipse(app, static_cast<blackhole*>(e));

        // white hole (foreground effect)
        for (auto e : entities)
            if (e->name == "whitehole")
                static_cast<Whitehole*>(e)->draw(app);

        // everything else (player, asteroids, bullets, explosions)
        for (auto e : entities)
            if (e->name != "blackhole" && e->name != "whitehole")
                e->draw(app);

        // warning overlay
        if (state == DANG_CHOI && bhState == blackholeState::DANGER && !blackholeTriggered)
        {
            float elapsedDanger = blackholeClock.getElapsedTime().asSeconds();
            float timeUntilBlackhole = triggerTime - elapsedDanger;

            if (timeUntilBlackhole <= BLACKHOLE_WARNING_TIME &&
                timeUntilBlackhole > 0.f)
            {
                if (!warningActive)
                {
                    warningActive = true;
                    sound.playAlert();
                }

                float blinkSpeed = 6.f;
                bool visible = static_cast<int>(elapsedDanger * blinkSpeed) % 2 == 0;

                if (visible)
                {
                    sf::RectangleShape warning(sf::Vector2f(W, H));
                    warning.setFillColor(sf::Color(255, 0, 0, 80));
                    app.draw(warning);
                }
            }
            else if (warningActive)
            {
                warningActive = false;
                sound.stopAlert();
            }
        }
        // edge punish warning 
        if (state == DANG_CHOI && edgePunish.isWarningActive())
        {
            float timeLeft = edgePunish.getWarningTimeLeft();

            if (timeLeft > 0.f)
            {
                float elapsed = 3.f - timeLeft;
                float blinkSpeed = 6.f;

                bool visible =
                    static_cast<int>(elapsed * blinkSpeed) % 2 == 0;

                if (visible)
                {
                    sf::RectangleShape warning(sf::Vector2f(W, H));
                    warning.setFillColor(sf::Color(255, 0, 0, 80));
                    app.draw(warning);
                }
            }
        }
        // Pause menu overlay ()
        if (state == PAUSE) 
        {
            RectangleShape overlay(Vector2f(W, H)); 
            overlay.setFillColor(Color(0, 0, 0, 150)); 
            app.draw(overlay);
   
            // Draw Pause menu options
            sContinue.setColor(Color(100, 100, 100)); 
            sRetry.setColor(Color(100, 100, 100)); 
            sSetting.setColor(Color(100, 100, 100)); 
            sExitPause.setColor(Color(100, 100, 100));
            sPause.setColor(Color::White);

            float buttonScale = 0.8f; 
            sContinue.setScale(buttonScale, buttonScale);
            sRetry.setScale(buttonScale, buttonScale);
            sSetting.setScale(0.5f, 0.5f);
            sExitPause.setScale(0.6f, 0.6f);
            sPause.setScale(buttonScale, buttonScale);
            sContinue.setPosition(W / 2 - 100, H / 2 - 200); 
            sRetry.setPosition(W / 2 - 100, H / 2 - 75);
            sSetting.setPosition(W / 2 - 80, H / 2 + 50);
            sExitPause.setPosition(W / 2 - 80, H / 2 + 175);
            sPause.setPosition(W / 2 - 330, H / 2 - 450);

            if (pauseIdx == 0) 
            {
                sContinue.setColor(Color::White);
                sContinue.setPosition(W / 2 - 100 + 30, H / 2 - 200); 
            }
            if (pauseIdx == 1) 
            {
                sRetry.setColor(Color::White);
                sRetry.setPosition(W / 2 - 100 + 30, H / 2 - 75);
            }
            if (pauseIdx == 2) 
            {
                sSetting.setColor(Color::White);
                sSetting.setPosition(W / 2 - 80 + 30, H / 2 + 50);
            }
            if (pauseIdx == 3) 
            {
                sExitPause.setColor(Color::White);
                sExitPause.setPosition(W / 2 - 80 + 30, H / 2 + 175);
           }
                
            app.draw(sPause);
            app.draw(sContinue); 
            app.draw(sRetry); 
            app.draw(sSetting);
            app.draw(sExitPause);
        }
      }

        app.display();

    }

    return 0;
}