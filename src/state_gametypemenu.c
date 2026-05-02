
#include "cgametypemenu.h"
#include "gamefuncs.h"
#include "defines.h"
#include "common.h"
#include "sound.h"
#include "state_gametypemenu.h"
#include "pd_api.h"

void GameTypeMenuInit()
{
    GameType = Fixed;
}
void GameTypeMenu()
{
    if (GameState == GSGameTypeMenuInit)
    {
        GameTypeMenuInit();
        GameState = GSGameTypeMenu;
    }
    if ((currButtons & kButtonUp) && !(prevButtons & kButtonUp))
        CGameTypeMenu_NextItem(MenuGameType);
    if ((currButtons & kButtonDown) && !(prevButtons & kButtonDown))    
        CGameTypeMenu_PreviousItem(MenuGameType);
    if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
    {
        playMenuAcknowlege();
        switch(CGameTypeMenu_GetSelection(MenuGameType))
        {
            case Fixed:
                GameType = Fixed;
                break;
            case Relative:
                GameType = Relative;
                break;
        }
        GameState = GSReadyGoInit;
    }
    if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
    {
        playMenuBackSound();
        GameState = GSTitleScreenInit;
    }
    CGameTypeMenu_Draw(MenuGameType);
}

