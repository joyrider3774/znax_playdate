#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "common.h"
#include "defines.h"
#include "cgametypemenu.h"
#include "cmainmenu.h"
#include "cselector.h"
#include "cworldparts.h"
#include "gamefuncs.h"
#include "state_gametypemenu.h"
#include "state_credits.h"
#include "state_titlescreen.h"
#include "state_timeover.h"
#include "state_readygo.h"
#include "state_intro.h"
#include "state_game.h"
#include "state_showhighscores.h"
#include "state_gethighscorename.h"
#include "gamefuncs.h"
#include "sound.h"
#include "Pd_helperfuncs.h"
#include "pd_api.h"

void resetGlobals() {
    IMG_timeover = NULL;
    IMG_highscores = NULL;
    IMG_background = NULL;
    IMG_ready = NULL;
    IMG_go = NULL;
    IMG_intro1 = NULL;
    IMG_intro2 = NULL;
    IMG_titlescreen = NULL;
    IMG_credits = NULL;
    IMG_cursor = NULL;
    IMG_play1 = NULL;
    IMG_play2 = NULL;
    IMG_highscores1 = NULL;
    IMG_highscores2 = NULL;
    IMG_credits1 = NULL;
    IMG_credits2 = NULL;
    IMG_selectgametype = NULL;
    IMG_fixedtimer1 = NULL;
    IMG_fixedtimer2 = NULL;
    IMG_relativetimer1 = NULL;
    IMG_relativetimer2 = NULL;
    IMG_blocks = NULL;

    menu1 = NULL;
    GlobalSoundEnabled = true;
    Timer = 150;
    AddToScore = 0;
    GameState = GSIntroInit;
    Score = 0;
    GameType = Fixed;
    Time = 0;
    ScoreTimer = 0;
    Counter = 0;
    movesLeft = 0;
    const char* err;
    font = pd->graphics->loadFont("/System/Fonts/Roobert-10-Bold", &err);
    World = CWorldParts_Create();
    Selector = CSelector_Create(NrOfCols / 2, NrOfRows / 2);
    MenuGameType = CGameTypeMenu_Create();
    MainMenu = CMainMenu_Create();
}

void setupGame() {
    resetGlobals();
    loadGraphics();
    LoadHighScores();
    initSound();
    initMusic();
    setSoundOn(true);
    setMusicOn(true);
    
    pd->graphics->setBackgroundColor(kColorWhite);
    pd->display->setOffset((LCD_COLUMNS - WINDOW_WIDTH) >> 1, (LCD_ROWS - WINDOW_HEIGHT) >> 1);
}

void terminateGame() {
    unloadGraphics();
    deInitSound();
    deInitMusic();
    CSelector_Destroy(Selector);
    CWorldParts_Destroy(World);
    CGameTypeMenu_Destroy(MenuGameType);
    CMainMenu_Destroy(MainMenu);
    pd->system->removeAllMenuItems();
}

int mainLoop(void* userdata) {
    prevButtons = currButtons;
    pd->system->getButtonState(&currButtons, NULL, NULL);
    pd->graphics->clear(kColorWhite);
    switch(GameState)
    {
        case GSGame :
        case GSGameInit:
            Game();
            break;
        case GSTitleScreen:
        case GSTitleScreenInit:
            TitleScreen();
            break;
        case GSIntro :
        case GSIntroInit :
            Intro();
            break;
        case GSReadyGo:
        case GSReadyGoInit:
            ReadyGo();
            break;
        case GSTimeOver:
        case GSTimeOverInit:
            TimeOver();
            break;
        case GSCredits:
        case GSCreditsInit:
            Credits();
            break;
        case GSGameTypeMenu:
        case GSGameTypeMenuInit:
            GameTypeMenu();
            break;
        case GSShowHighScores:
        case GSShowHighScoresInit:
            ShowHighScores();
            break;
        case GSGetHighScoreName:
        case GSGetHighScoreNameInit:
            GetHighScoreName();
            break;
        default :
            break;
    }
    return 1;
}