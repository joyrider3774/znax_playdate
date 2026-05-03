
#include "gamefuncs.h"
#include "common.h"
#include "defines.h"
#include "cmainmenu.h"
#include "state_titlescreen.h"
#include "sound.h"
#include "pd_api.h"
#include "Pd_helperfuncs.h"
#include "gamefuncs.h"

void MenuItem1Callback(void* userdata)
{
    ResetHighScores();
    SaveHighScores();
}

void TitleScreenInit()
{
    SelectMusic(musTitle, 0);
    if (menu1 == NULL)
    {
        menu1 = pd->system->addMenuItem("Clear HiScore", MenuItem1Callback, NULL);
    }
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
                if (menu1)
                {
                    pd->system->removeMenuItem(menu1);
                    menu1 = NULL;
                }
                break;
            case 2:
                //so that it shows both gameplay modes
                GameType = Fixed;
                GameState = GSShowHighScoresInit;
                break;
            case 3:
                GameState = GSCreditsInit;
                if (menu1)
                {
                    pd->system->removeMenuItem(menu1);
                    menu1 = NULL;
                }
                break;
            default:
                break;
        }
    }
    CMainMenu_Draw(MainMenu);
}
