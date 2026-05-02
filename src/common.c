#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "cselector.h"
#include "cgametypemenu.h"
#include "cmainmenu.h"
#include <stdbool.h>
#include <stdint.h>
#include <pd_api.h>

LCDBitmap *IMG_timeover = NULL, *IMG_highscores = NULL, *IMG_background=NULL, *IMG_ready=NULL, *IMG_go=NULL, * IMG_intro1= NULL, *IMG_intro2=NULL, *IMG_titlescreen=NULL,
	*IMG_credits=NULL, *IMG_cursor=NULL, *IMG_play1=NULL, *IMG_play2=NULL, *IMG_highscores1=NULL, *IMG_highscores2=NULL, *IMG_credits1=NULL, *IMG_credits2=NULL,
	*IMG_selectgametype=NULL, *IMG_fixedtimer1=NULL, * IMG_fixedtimer2 = NULL, * IMG_relativetimer1 = NULL, * IMG_relativetimer2 = NULL;
LCDBitmapTable* IMG_blocks = NULL;

struct CWorldParts;

bool GlobalSoundEnabled = true;
int Timer = 150, AddToScore = 0;
int GameState = GSIntro;

long int Score;
int GameType = Fixed;
SaveData saveData;
CSelector* Selector;
CGameTypeMenu *MenuGameType;
uint32_t Time;
uint32_t ScoreTimer;
int Counter;
CMainMenu *MainMenu;
PDButtons currButtons, prevButtons;
int movesLeft = 0;
LCDFont* font;