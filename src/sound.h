#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>


#define musNone 0
#define musTitle 1


void playSelectSound();
void playErrorSound();
void playMenuSelectSound();
void playMenuBackSound();
void playMenuAcknowlege();
void playThreeSound();
void playTwoSound();
void playOneSound();
void playDeleteSound();
void playFiveMinuteSound();
void playOnMinuteSound();
void playReadyGoSound();
void playWelcomeSound();
void playTimeOverSound();

void initSound();
void deInitSound();
void SelectMusic(uint8_t musicFile, uint8_t loop);
void initMusic();
void deInitMusic();
void setMusicOn(uint8_t value);
void setSoundOn(uint8_t value);
uint8_t isMusicOn();
uint8_t isSoundOn();

#endif