#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>

class SoundManager
{
public:
    SoundManager();

    // Sound effects
    void playShoot();
    void playExplosion();
    void playDestroyed();
    void playBlackhole();
    void playWhitehole();
    void playAlert();
    void playWarning();
    void playEnter();

    // Stop alert sound
    void stopAlert();
    void stopWarning();

    // Music control
    void setVolume(float volume);
    float getVolume() const { return currentVol; }
    void playMenuMusic();
    void playGameMusic();
    void stopAllMusic();

private:
    // defaut volume
    float currentVol = 100.0f;

    // Buffers
    sf::SoundBuffer shootBuffer;
    sf::SoundBuffer explosionBuffer;
    sf::SoundBuffer destroyedBuffer;
    sf::SoundBuffer blackholeBuffer;
    sf::SoundBuffer whiteholeBuffer;
    sf::SoundBuffer alertBuffer;
    sf::SoundBuffer warningBuffer;
    sf::SoundBuffer enterBuffer;

    // Sounds
    sf::Sound shootSound;
    sf::Sound explosionSound;
    sf::Sound destroyedSound;
    sf::Sound blackholeSound;
    sf::Sound whiteholeSound;
    sf::Sound alertSound;
    sf::Sound warningSound;
    sf::Sound enterSound;

    // Music
    sf::Music menuMusic;
    sf::Music gameMusic;
};

#endif // SOUND_H