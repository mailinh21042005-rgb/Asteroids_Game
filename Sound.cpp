#include "Sound.h"
#include <iostream>

SoundManager::SoundManager()
{
    if (!shootBuffer.loadFromFile("sounds/shoot.wav"))
        std::cout << "Failed to load shoot.wav\n";

    if (!explosionBuffer.loadFromFile("sounds/explosion_mete.wav"))
        std::cout << "Failed to load explosion_mete.wav\n";

    if (!destroyedBuffer.loadFromFile("sounds/die.mp3"))
        std::cout << "Failed to load die.mp3\n";

    if (!blackholeBuffer.loadFromFile("sounds/release.mp3"))
        std::cout << "Failed to load release.mp3\n";

    if (!whiteholeBuffer.loadFromFile("sounds/release.mp3"))
        std::cout << "Failed to load release.mp3\n";

    if (!alertBuffer.loadFromFile("sounds/alert.mp3"))
        std::cout << "Failed to load alert.mp3\n";

    if (!enterBuffer.loadFromFile("sounds/click.wav"))
        std::cout << "Failed to load enter.wav\n";
    
    if (!menuMusic.openFromFile("sounds/intro.mp3"))
        std::cout << "Failed to load intro.mp3\n";
    
    if (!gameMusic.openFromFile("sounds/background.mp3"))
        std::cout << "Failed to load background.mp3\n";

    if (!warningBuffer.loadFromFile("sounds/warning.mp3"))
        std::cout << "Failed to load warning.mp3\n";

    menuMusic.setLoop(true);
    gameMusic.setLoop(true);

    shootSound.setBuffer(shootBuffer);
    explosionSound.setBuffer(explosionBuffer);
    destroyedSound.setBuffer(destroyedBuffer);
    blackholeSound.setBuffer(blackholeBuffer);
    whiteholeSound.setBuffer(whiteholeBuffer);
    alertSound.setBuffer(alertBuffer);
    enterSound.setBuffer(enterBuffer);
    warningSound.setBuffer(warningBuffer);
    
}

void SoundManager::setVolume(float volume)
{
    currentVol = volume;

    shootSound.setVolume(currentVol * 0.5f);
    explosionSound.setVolume(currentVol * 0.8f);
    destroyedSound.setVolume(currentVol * 0.7f);
    blackholeSound.setVolume(currentVol);
    whiteholeSound.setVolume(currentVol);
    alertSound.setVolume(currentVol * 0.8f);
    enterSound.setVolume(currentVol);
    menuMusic.setVolume(currentVol);
    gameMusic.setVolume(currentVol);
    warningSound.setVolume(currentVol * 0.8f);
}

void SoundManager::playShoot()
{
    shootSound.play();
}

void SoundManager::playExplosion()
{
    explosionSound.play();
}

void SoundManager::playDestroyed()
{
    destroyedSound.play();
}

void SoundManager::playBlackhole()
{
    blackholeSound.play();
}

void SoundManager::playWhitehole()
{
    whiteholeSound.play();
}

void SoundManager::playAlert()
{
    alertSound.play();
}
void SoundManager::playWarning()
{
    warningSound.play();
}

void SoundManager::playMenuMusic()
{
    if (gameMusic.getStatus() == sf::Music::Playing)
        gameMusic.stop();

    if (menuMusic.getStatus() != sf::Music::Playing)
        menuMusic.play();
}

void SoundManager::playGameMusic()
{
    if (menuMusic.getStatus() == sf::Music::Playing)
        menuMusic.stop();

    if (gameMusic.getStatus() != sf::Music::Playing)
        gameMusic.play();
}

void SoundManager::stopAllMusic()
{
    menuMusic.stop();
    gameMusic.stop();
}

void SoundManager::playEnter()
{
    enterSound.play();
}

void SoundManager::stopAlert()
{
    alertSound.stop();
}

void SoundManager::stopWarning()
{
    warningSound.stop();
}