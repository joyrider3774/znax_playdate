#include "gamefuncs.h"
#include "defines.h"
#include "common.h"
#include "cworldparts.h"
#include "cselector.h"
#include "state_game.h"
#include "sound.h"
#include "pd_api.h"
#include "Pd_helperfuncs.h"

void GameInit()
{
    AddToScore = 0;
    if(GameType == Relative)
        Timer = 150;
    else
        Timer = 300;
    Time = pd->system->getCurrentTimeMilliseconds();
    ScoreTimer = 0;
    Selector->CurrentPoint.X = NrOfCols / 2;
    Selector->CurrentPoint.Y = NrOfRows / 2;
}

void Game()
{
    if (GameState == GSGameInit)
    {
        GameInit();
        GameState = GSGame;
    }
    
    if ((currButtons & kButtonLeft) && !(prevButtons & kButtonLeft))
        CSelector_SetPosition(Selector, Selector->CurrentPoint.X -1,Selector->CurrentPoint.Y);
    if ((currButtons & kButtonRight) && !(prevButtons & kButtonRight))        
        CSelector_SetPosition(Selector, Selector->CurrentPoint.X +1,Selector->CurrentPoint.Y);
    if ((currButtons & kButtonUp) && !(prevButtons & kButtonUp))
        CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y-1);
    if ((currButtons & kButtonDown) && !(prevButtons & kButtonDown))
        CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y+1);
    if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
    {
        playMenuBackSound();
        GameState = GSTitleScreenInit;
    }
    if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
    {
        AddToScore+= CWorldParts_Select(World, Selector->CurrentPoint.X,Selector->CurrentPoint.Y);
        if(AddToScore != 0)
        {
            ScoreTimer = pd->system->getCurrentTimeMilliseconds() + 700;
        }
    }
    CWorldParts_Draw(World);
    CSelector_Draw(Selector);
    if(AddToScore !=0)
    {
        if(ScoreTimer <= pd->system->getCurrentTimeMilliseconds())
        {
            ScoreTimer = 0;
            Score +=AddToScore;
            if (GameType == Relative)
                Timer += AddToScore / 400;
            AddToScore = 0;
        }
    }
    DrawStatusBar();
    if (Time +1000 < pd->system->getCurrentTimeMilliseconds())
    {
        Timer-= 1;
        switch (Timer)
        {
            case 60*5 :
                playFiveMinuteSound();
                break;
            case 60:
                playOnMinuteSound();
                break;
            case 3 :
                playThreeSound();
                break;
            case 2 :
                playTwoSound();
                break;
            case 1 :
                playOneSound();
                break;
            case 0 :
                if(ScoreTimer != 0)
                {
                    Score += AddToScore;
                    if(GameType == Relative)
                        Timer += AddToScore / 200;
                }
                if(Timer == 0)
                {
                    playTimeOverSound();
                    GameState = GSTimeOverInit;
                }
                break;
        }
        Time = pd->system->getCurrentTimeMilliseconds();
    }
}
