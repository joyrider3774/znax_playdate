#include <stdint.h>
#include <string.h>
#include "sound.h"
#include "common.h"
#include "Pd_helperfuncs.h"
#include "pd_api.h"

uint8_t music_on, sound_on, prev_music;

FilePlayer* MusicPlayer;
SamplePlayer* BlockSelectPlayer, * deletePlayer, * errorPlayer, * fiveminutePlayer, * menuPlayer, * onePlayer, * oneminutePlayer,
* readygoPlayer, * selectPlayer, * threePlayer, * timeoverPlayer, * twoPlayer, * welcomePlayer;
AudioSample *BlockSelectSample, * deleteSample, * errorSample, * fiveminuteSample, * menuSample, * oneSample, * oneminuteSample,
* readygoSample, * selectSample, * threeSample, * timeoverSample, * twoSample, * welcomeSample;

void setMusicOn(uint8_t value)
{
    music_on = value;
}


void SelectMusic(uint8_t musicFile, uint8_t loop)
{
    if (prev_music != musicFile)
    {
		prev_music = musicFile;
        switch (musicFile)
        {
            case musTitle:
                pd->sound->fileplayer->loadIntoPlayer(MusicPlayer, "music/title");
                pd->sound->fileplayer->play(MusicPlayer, loop);
                break;
            default:
                break;
        }
    }
}

void loadSounds()
{   
    BlockSelectSample = pd->sound->sample->load("sound/blockselect");
    deleteSample = pd->sound->sample->load("sound/delete");
    errorSample = pd->sound->sample->load("sound/error");
    fiveminuteSample = pd->sound->sample->load("sound/fiveminute");
    menuSample = pd->sound->sample->load("sound/menu");
    oneSample = pd->sound->sample->load("sound/one");
    oneminuteSample = pd->sound->sample->load("sound/oneminute");
    readygoSample = pd->sound->sample->load("sound/readygo");
    selectSample = pd->sound->sample->load("sound/select");
    threeSample = pd->sound->sample->load("sound/three");
    timeoverSample = pd->sound->sample->load("sound/timeover");
    twoSample = pd->sound->sample->load("sound/two");
    welcomeSample = pd->sound->sample->load("sound/welcome");

    
    BlockSelectPlayer = pd->sound->sampleplayer->newPlayer();
    deletePlayer = pd->sound->sampleplayer->newPlayer();
    errorPlayer = pd->sound->sampleplayer->newPlayer();
    fiveminutePlayer = pd->sound->sampleplayer->newPlayer();
    menuPlayer = pd->sound->sampleplayer->newPlayer();
    onePlayer = pd->sound->sampleplayer->newPlayer();
    oneminutePlayer = pd->sound->sampleplayer->newPlayer();
    readygoPlayer = pd->sound->sampleplayer->newPlayer();
    selectPlayer = pd->sound->sampleplayer->newPlayer();
    threePlayer = pd->sound->sampleplayer->newPlayer();
    timeoverPlayer = pd->sound->sampleplayer->newPlayer();
    twoPlayer = pd->sound->sampleplayer->newPlayer();
    welcomePlayer = pd->sound->sampleplayer->newPlayer();


    pd->sound->sampleplayer->setSample(BlockSelectPlayer, BlockSelectSample);
    pd->sound->sampleplayer->setSample(deletePlayer, deleteSample);
    pd->sound->sampleplayer->setSample(errorPlayer, errorSample);
    pd->sound->sampleplayer->setSample(fiveminutePlayer, fiveminuteSample);
    pd->sound->sampleplayer->setSample(menuPlayer, menuSample);
    pd->sound->sampleplayer->setSample(onePlayer, oneSample);
    pd->sound->sampleplayer->setSample(oneminutePlayer, oneminuteSample);
    pd->sound->sampleplayer->setSample(readygoPlayer, readygoSample);
    pd->sound->sampleplayer->setSample(selectPlayer, selectSample);
    pd->sound->sampleplayer->setSample(threePlayer, threeSample);
    pd->sound->sampleplayer->setSample(timeoverPlayer, timeoverSample);
    pd->sound->sampleplayer->setSample(twoPlayer, twoSample);
    pd->sound->sampleplayer->setSample(welcomePlayer, welcomeSample);
}

void unloadSounds()
{
    pd->sound->sampleplayer->stop(BlockSelectPlayer);
    pd->sound->sampleplayer->stop(deletePlayer);
    pd->sound->sampleplayer->stop(errorPlayer);
    pd->sound->sampleplayer->stop(fiveminutePlayer);
    pd->sound->sampleplayer->stop(menuPlayer);
    pd->sound->sampleplayer->stop(onePlayer);
    pd->sound->sampleplayer->stop(oneminutePlayer);
    pd->sound->sampleplayer->stop(readygoPlayer);
    pd->sound->sampleplayer->stop(selectPlayer);
    pd->sound->sampleplayer->stop(threePlayer);
    pd->sound->sampleplayer->stop(timeoverPlayer);
    pd->sound->sampleplayer->stop(twoPlayer);
    pd->sound->sampleplayer->stop(welcomePlayer);

    pd->sound->sampleplayer->freePlayer(BlockSelectPlayer);
    pd->sound->sampleplayer->freePlayer(deletePlayer);
    pd->sound->sampleplayer->freePlayer(errorPlayer);
    pd->sound->sampleplayer->freePlayer(fiveminutePlayer);
    pd->sound->sampleplayer->freePlayer(menuPlayer);
    pd->sound->sampleplayer->freePlayer(onePlayer);
    pd->sound->sampleplayer->freePlayer(oneminutePlayer);
    pd->sound->sampleplayer->freePlayer(readygoPlayer);
    pd->sound->sampleplayer->freePlayer(selectPlayer);
    pd->sound->sampleplayer->freePlayer(threePlayer);
    pd->sound->sampleplayer->freePlayer(timeoverPlayer);
    pd->sound->sampleplayer->freePlayer(twoPlayer);
    pd->sound->sampleplayer->freePlayer(welcomePlayer);

    pd->sound->sample->freeSample(BlockSelectSample);
    pd->sound->sample->freeSample(deleteSample);
    pd->sound->sample->freeSample(errorSample);
    pd->sound->sample->freeSample(menuSample);
    pd->sound->sample->freeSample(oneSample);
    pd->sound->sample->freeSample(oneminuteSample);
    pd->sound->sample->freeSample(readygoSample);
    pd->sound->sample->freeSample(selectSample);
    pd->sound->sample->freeSample(threeSample);
    pd->sound->sample->freeSample(timeoverSample);
    pd->sound->sample->freeSample(twoSample);
    pd->sound->sample->freeSample(welcomeSample);
}

void initMusic()
{
	prev_music = 0;
    MusicPlayer = pd->sound->fileplayer->newPlayer();
}

void deInitMusic()
{
    pd->sound->fileplayer->stop(MusicPlayer);
    pd->sound->fileplayer->freePlayer(MusicPlayer);
}

void setSoundOn(uint8_t value)
{
    sound_on = value;
}

uint8_t isMusicOn()
{
    return music_on;
}

uint8_t isSoundOn()
{
    return sound_on;
}

void initSound()
{
    sound_on = 0;
    loadSounds();
}

void deInitSound()
{
    unloadSounds();
}

void playTimeOverSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(timeoverPlayer, 1, 1.0f);
    }
}

void playWelcomeSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(welcomePlayer, 1, 1.0f);
    }
}

void playReadyGoSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(readygoPlayer, 1, 1.0f);
    }
}

void playOnMinuteSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(oneminutePlayer, 1, 1.0f);
    }
}

void playFiveMinuteSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(fiveminutePlayer, 1, 1.0f);
    }
}

void playDeleteSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(deletePlayer, 1, 1.0f);
    }
}


void playThreeSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(threePlayer, 1, 1.0f);
    }
}

void playTwoSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(twoPlayer, 1, 1.0f);
    }
}

void playOneSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(onePlayer, 1, 1.0f);
    }
}

void playSelectSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(BlockSelectPlayer, 1, 1.0f);
    }
}


void playErrorSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(errorPlayer, 1, 1.0f);
    }
}


void playMenuSelectSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(menuPlayer, 1, 1.0f);
    }
}

void playMenuBackSound(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(selectPlayer, 1, 1.0f);
    }
}

void playMenuAcknowlege(void)
{
    if (sound_on)
    {
        pd->sound->sampleplayer->play(selectPlayer, 1, 1.0f);
    }
}