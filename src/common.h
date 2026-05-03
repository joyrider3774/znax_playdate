#ifndef COMMON_H
#define COMMON_H

#include <inttypes.h>
#include "defines.h"
#include "cworldparts.h"
#include <stdbool.h>
#include "cselector.h"
#include "cgametypemenu.h"
#include "cmainmenu.h"
#include "pd_api.h"

extern LCDBitmap *IMG_timeover, *IMG_highscores, * IMG_background, * IMG_ready, * IMG_go, * IMG_intro1, *IMG_intro2, *IMG_titlescreen, * IMG_credits, * IMG_cursor,
	* IMG_play1, * IMG_play2, * IMG_highscores1, * IMG_highscores2, * IMG_credits1, * IMG_credits2, * IMG_selectgametype, * IMG_fixedtimer1, * IMG_fixedtimer2,
	* IMG_relativetimer1, * IMG_relativetimer2;
extern LCDBitmapTable* IMG_blocks;
extern LCDFont* font;
extern PDMenuItem *menu1;
extern bool GlobalSoundEnabled;
extern int Timer, AddToScore;
extern int GameState;
extern long int Score;
extern int GameType;
extern SaveData saveData;
extern CSelector* Selector;
extern CGameTypeMenu *MenuGameType;
extern uint32_t Time;
extern uint32_t ScoreTimer;
extern int Counter;
extern CMainMenu *MainMenu;
extern PDButtons currButtons, prevButtons;
extern int movesLeft;
#endif