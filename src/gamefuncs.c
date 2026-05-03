#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "defines.h"
#include "Pd_helperfuncs.h"
#include "pd_api.h"

#define SAVE_MAGIC 0xDADA

uint8_t calcCRC(void *data, size_t len) {
  uint8_t crc = 0;
  uint8_t *ptr = (uint8_t *)data;
  for (size_t i = 0; i < len; i++) {
    crc ^= ptr[i];
    for (uint8_t j = 0; j < 8; j++) {
      if (crc & 0x80)
        crc = (crc << 1) ^ 0x07;
      else
        crc <<= 1;
    }
  }
  return crc;
}

void ResetHighScores()
{
    memset(&saveData, 0, sizeof(SaveData));
    saveData.magic = SAVE_MAGIC;

    for (int Teller = 0; Teller < 10; Teller++)
    {
        strcpy(saveData.HighScores[Fixed][Teller].PName, "joyrider");
        strcpy(saveData.HighScores[Relative][Teller].PName, "joyrider");
        saveData.HighScores[Fixed][Teller].PScore = 0;
        saveData.HighScores[Relative][Teller].PScore = 0;
    }
}

void LoadHighScores()
{
    SDFile* File = pd->file->open("savedata", kFileReadData);
    if (File)
    {
        pd->file->read(File, &saveData, sizeof(SaveData));
        pd->file->close(File);
    }
    //needs to be -uint8t size because of crc not included in calculation
    uint8_t crc = calcCRC(&saveData, sizeof(SaveData) - sizeof(uint8_t));
    if (saveData.magic != SAVE_MAGIC || saveData.crc != crc) 
    {
        ResetHighScores();
    }
}

void SaveHighScores()
{
    SDFile* File = pd->file->open("savedata", kFileWrite);
    if (File)
    {
        saveData.crc = calcCRC(&saveData, sizeof(SaveData) - sizeof(uint8_t));
        pd->file->write(File, &saveData, sizeof(SaveData));
        pd->file->close(File);
    }
}

void DrawStatusBar()
{
    char *Text;
    if (AddToScore == 0)
    {
        pd->system->formatString(&Text, "TIME:\n%02d:%02d\n     \n\nSCORE:\n%d\n\n\nLEFT:\n%d", Timer / 60, Timer % 60, Score, movesLeft);
    }
    else
    {
        if (GameType == Relative)
        {
            pd->system->formatString(&Text, "TIME:\n%02d:%02d\n+%03d\n\nSCORE:\n%d\n+%d\n\nLEFT:\n%d", Timer / 60, Timer % 60, AddToScore / 400, Score, AddToScore, movesLeft);
        }
        else
        {
            pd->system->formatString(&Text, "TIME:\n%02d:%02d\n     \n\nSCORE:\n%d\n+%d\n\nLEFT:\n%d", Timer / 60, Timer % 60, Score, AddToScore, movesLeft);
        }
    }

    drawTextColor(true, NULL, font, Text, strlen(Text), kASCIIEncoding, 247, 10, kColorBlack, false);

    pd->system->realloc(Text, 0);
}

char chr(int ascii)
{
	return((char)ascii);
}

int ord(char chr)
{
	return((int)chr);
}

void loadGraphics()
{
    const char* err;
    IMG_timeover = pd->graphics->loadBitmap("images/timeover", &err);  
    IMG_highscores = pd->graphics->loadBitmap("images/highscores", &err); 
    IMG_background = pd->graphics->loadBitmap("images/background", &err); 
    IMG_ready = pd->graphics->loadBitmap("images/ready", &err); 
    IMG_go = pd->graphics->loadBitmap("images/go", &err); 
    IMG_intro1 = pd->graphics->loadBitmap("images/intro1", &err);
    IMG_intro2 = pd->graphics->loadBitmap("images/intro2", &err);
    IMG_titlescreen = pd->graphics->loadBitmap("images/titlescreen", &err);
    IMG_credits = pd->graphics->loadBitmap("images/credits", &err);
    IMG_cursor = pd->graphics->loadBitmap("images/cursor", &err);
    IMG_play1 = pd->graphics->loadBitmap("images/play1", &err);
    IMG_play2 = pd->graphics->loadBitmap("images/play2", &err);
    IMG_highscores1 = pd->graphics->loadBitmap("images/highscores1", &err);
    IMG_highscores2 = pd->graphics->loadBitmap("images/highscores2", &err); 
    IMG_credits1 = pd->graphics->loadBitmap("images/credits1", &err);
    IMG_credits2 = pd->graphics->loadBitmap("images/credits2", &err);
    IMG_selectgametype = pd->graphics->loadBitmap("images/selectgame", &err);
    IMG_fixedtimer1 = pd->graphics->loadBitmap("images/fixedtimer1", &err);
    IMG_fixedtimer2 = pd->graphics->loadBitmap("images/fixedtimer2", &err);
    IMG_relativetimer1 = pd->graphics->loadBitmap("images/relativetimer1", &err);
    IMG_relativetimer2 = pd->graphics->loadBitmap("images/relativetimer2", &err); 

    IMG_blocks = pd->graphics->loadBitmapTable("images/blocks", &err);
}

void unloadGraphics()
{
    if (IMG_timeover)
        pd->graphics->freeBitmap(IMG_timeover);
    if (IMG_highscores)
        pd->graphics->freeBitmap(IMG_highscores);
    if (IMG_background)
        pd->graphics->freeBitmap(IMG_background);
    if (IMG_ready)
        pd->graphics->freeBitmap(IMG_ready);
    if (IMG_go)
        pd->graphics->freeBitmap(IMG_go);
    if (IMG_intro1)
        pd->graphics->freeBitmap(IMG_intro1);
    if (IMG_intro2)
        pd->graphics->freeBitmap(IMG_intro2);
    if (IMG_titlescreen)
        pd->graphics->freeBitmap(IMG_titlescreen);
    if (IMG_credits)
        pd->graphics->freeBitmap(IMG_credits);
    if (IMG_cursor)
        pd->graphics->freeBitmap(IMG_cursor);
    if (IMG_play1)
        pd->graphics->freeBitmap(IMG_play1);
    if (IMG_play2)
        pd->graphics->freeBitmap(IMG_play2);
    if (IMG_highscores1)
        pd->graphics->freeBitmap(IMG_highscores1);
    if (IMG_highscores2)
        pd->graphics->freeBitmap(IMG_highscores2);
    if (IMG_credits1)
        pd->graphics->freeBitmap(IMG_credits1);
    if (IMG_credits2)
        pd->graphics->freeBitmap(IMG_credits2);
    if (IMG_selectgametype)
        pd->graphics->freeBitmap(IMG_selectgametype);
    if (IMG_fixedtimer1)
        pd->graphics->freeBitmap(IMG_fixedtimer1);
    if (IMG_fixedtimer2)
        pd->graphics->freeBitmap(IMG_fixedtimer2);
    if (IMG_relativetimer1)
        pd->graphics->freeBitmap(IMG_relativetimer1);
    if (IMG_relativetimer2)
        pd->graphics->freeBitmap(IMG_relativetimer2);

    if (IMG_blocks)
        pd->graphics->freeBitmapTable(IMG_blocks);
}
