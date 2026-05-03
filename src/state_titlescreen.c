
#include "gamefuncs.h"
#include "common.h"
#include "defines.h"
#include "cmainmenu.h"
#include "state_titlescreen.h"
#include "sound.h"
#include "pd_api.h"
#include "Pd_helperfuncs.h"
#include "gamefuncs.h"
#include "sound.h"

void MenuItem1Callback(void* userdata)
{
    int tmp = pd->system->getMenuItemValue(menu1);
    setMusicOn(tmp);
    if (isMusicOn())
    {
        SelectMusic(musNone, 0);
        SelectMusic(musTitle, 0);
    }
    SaveSettings();
}

void MenuItem2Callback(void* userdata)
{
    int tmp = pd->system->getMenuItemValue(menu2);
    setSoundOn(tmp);
    SaveSettings();
}

void MenuItem3Callback(void* userdata)
{
    ResetHighScores();
    SaveHighScores();
    playMenuAcknowlege();
}

void TitleScreenInit()
{
    SelectMusic(musTitle, 0);
    if (menu1 == NULL)
    {
        menu1 = pd->system->addCheckmarkMenuItem("Music", isMusicOn(), MenuItem1Callback, NULL);
    }
    
    if (menu2 == NULL)
    {
        menu2 = pd->system->addCheckmarkMenuItem("Sound", isSoundOn(), MenuItem2Callback, NULL);
    }

    if (menu3 == NULL)
    {
        menu3 = pd->system->addMenuItem("Clear HiScore", MenuItem3Callback, NULL);
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
                if (menu3)
                {
                    pd->system->removeMenuItem(menu3);
                    menu3 = NULL;
                }
                break;
            case 2:
                //so that it shows both gameplay modes
                GameType = Fixed;
                GameState = GSShowHighScoresInit;
                break;
            case 3:
                GameState = GSCreditsInit;
                if (menu3)
                {
                    pd->system->removeMenuItem(menu3);
                    menu3 = NULL;
                }
                break;
            default:
                break;
        }
    }
    CMainMenu_Draw(MainMenu);
}
