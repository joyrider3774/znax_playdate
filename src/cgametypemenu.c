#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "defines.h"
#include "cgametypemenu.h"
#include "sound.h"
#include "Pd_helperfuncs.h"
#include "pd_api.h"

// constructor of main menu will Load the graphics and set the current selection to 1 (io newgame)
CGameTypeMenu* CGameTypeMenu_Create()
{
    CGameTypeMenu* Result = (CGameTypeMenu*) malloc(sizeof(CGameTypeMenu));
    Result->Selection = Fixed;
    return Result;
}

// return the current selection
int CGameTypeMenu_GetSelection(CGameTypeMenu* GameTypeMenu) 
{
    return GameTypeMenu->Selection;
}

// Destructor will free the surface images
void CGameTypeMenu_Destroy(CGameTypeMenu* GameTypeMenu)
{
    free(GameTypeMenu);
    GameTypeMenu = NULL;
}

// Increase the selection if it goes to far set i to the first selection
void CGameTypeMenu_NextItem(CGameTypeMenu* GameTypeMenu)
{
    GameTypeMenu->Selection++;
    if (GameTypeMenu->Selection == 2)
        GameTypeMenu->Selection = 0;
    playMenuSelectSound();
}

// decrease the selection if it goes to low set it to the last selection
void CGameTypeMenu_PreviousItem(CGameTypeMenu* GameTypeMenu)
{
    GameTypeMenu->Selection--;
    if (GameTypeMenu->Selection == -1)
        GameTypeMenu->Selection = 1;
    playMenuSelectSound();
}

// Draw the main menu
void CGameTypeMenu_Draw(CGameTypeMenu* GameTypeMenu)
{
    pd->graphics->drawBitmap(IMG_titlescreen, 0, 0, kBitmapUnflipped);
    pd->graphics->drawBitmap(IMG_selectgametype, 68, 77, kBitmapUnflipped);
    
    if (GameTypeMenu->Selection == Fixed)
    {
        pd->graphics->drawBitmap(IMG_fixedtimer2, 68, 114, kBitmapUnflipped);
    }
    else
    {
        pd->graphics->drawBitmap(IMG_fixedtimer1, 68, 114, kBitmapUnflipped);
    }

    if (GameTypeMenu->Selection == Relative)
    {
        pd->graphics->drawBitmap(IMG_relativetimer2, 68, 151, kBitmapUnflipped);
    }
    else
    {
        pd->graphics->drawBitmap(IMG_relativetimer1, 68, 151, kBitmapUnflipped);
    }
}
