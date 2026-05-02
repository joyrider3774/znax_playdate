#include <stdlib.h>
#include "defines.h"
#include "common.h"
#include "cmainmenu.h"
#include "sound.h"
#include "Pd_helperfuncs.h"
#include "pd_api.h"

// constructor of main menu will Load the graphics and set the current selection to 1 (io newgame)
CMainMenu* CMainMenu_Create()
{
    CMainMenu* Result = (CMainMenu*) malloc(sizeof(CMainMenu));
    Result->Selection = 1;
    return Result;
}

// destructor
void CMainMenu_Destroy(CMainMenu* MainMenu)
{
    free(MainMenu);
    MainMenu = NULL;
}

// return the current selection
int CMainMenu_GetSelection(CMainMenu* MainMenu) 
{
    return MainMenu->Selection;
}

// Increase the selection if it goes to far set i to the first selection
void CMainMenu_NextItem(CMainMenu* MainMenu)
{
    MainMenu->Selection++;
    if (MainMenu->Selection == 4)
        MainMenu->Selection = 1;
    playMenuSelectSound();
}

// decrease the selection if it goes to low set it to the last selection
void CMainMenu_PreviousItem(CMainMenu* MainMenu)
{
    MainMenu->Selection--;
    if (MainMenu->Selection == 0)
        MainMenu->Selection = 3;
    playMenuSelectSound();
}

// Draw the main menu
void CMainMenu_Draw(CMainMenu* MainMenu)
{
    pd->graphics->drawBitmap(IMG_titlescreen, 0, 0, kBitmapUnflipped);
    if (MainMenu->Selection == 1)
    {
        pd->graphics->drawBitmap(IMG_play2, 98, 73, kBitmapUnflipped);
    }
    else
    {
        pd->graphics->drawBitmap(IMG_play1, 98, 73, kBitmapUnflipped);
    }

    if (MainMenu->Selection == 2)
    {
        pd->graphics->drawBitmap(IMG_highscores2, 98, 105, kBitmapUnflipped);
    }
    else
    {
        pd->graphics->drawBitmap(IMG_highscores1, 98, 105, kBitmapUnflipped);
    }


    if (MainMenu->Selection == 3)
    {
        pd->graphics->drawBitmap(IMG_credits2, 98, 137, kBitmapUnflipped);
    }
    else
    {
        pd->graphics->drawBitmap(IMG_credits1, 98, 137, kBitmapUnflipped);
    }
}
