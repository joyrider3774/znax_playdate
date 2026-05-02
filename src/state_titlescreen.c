
#include "gamefuncs.h"
#include "common.h"
#include "defines.h"
#include "cmainmenu.h"
#include "state_titlescreen.h"
#include "sound.h"


void TitleScreenInit()
{
    SelectMusic(musTitle, 0);
}

void TitleScreen()
{    
    if (GameState == GSTitleScreenInit)
    {
        TitleScreenInit();
        GameState = GSTitleScreen;
    }
    
    if ((currButtons & kButtonUp) && !(prevButtons & kButtonUp))
        CMainMenu_PreviousItem(MainMenu);
    if ((currButtons & kButtonDown) && !(prevButtons & kButtonDown))  
        CMainMenu_NextItem(MainMenu);
    if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
    {      
        playMenuAcknowlege();
        switch(CMainMenu_GetSelection(MainMenu))
        {
            case 1:
                GameState = GSGameTypeMenuInit;
                break;
            case 2:
                //so that it shows both gameplay modes
                GameType = Fixed;
                GameState = GSShowHighScoresInit;
                break;
            case 3:
                GameState = GSCreditsInit;
                break;
            default:
                break;
        }
    }
    CMainMenu_Draw(MainMenu);
}
