#include <stdlib.h>
#include "gamefuncs.h"
#include "defines.h"
#include "common.h"
#include "cworldparts.h"
#include "sound.h"
#include "state_readygo.h"
#include "Pd_helperfuncs.h"
#include "pd_api.h"

void ReadyGoInit()
{
    srand(pd->system->getCurrentTimeMilliseconds());
    CWorldParts_NewGame(World);
    Score = 0;
    Time = pd->system->getCurrentTimeMilliseconds();
    Counter=0;
    if(GameType == Relative)
        Timer = 150;
    else
        Timer = 300;
}
void ReadyGo()
{
    
    if(GameState == GSReadyGoInit)
    {
        ReadyGoInit();
        GameState = GSReadyGo;
    }
    
    if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
    {
        playMenuBackSound();
        GameState = GSTitleScreenInit;
    }

       
    CWorldParts_Draw(World);
    int img_width, img_height;
    switch(Counter)
    {
        case 1 :
            pd->graphics->getBitmapData(IMG_ready, &img_width, &img_height, NULL, NULL, NULL);
            pd->graphics->drawBitmap(IMG_ready, (WINDOW_WIDTH- img_width) >> 1, (WINDOW_HEIGHT - img_height) >> 1, kBitmapUnflipped);
            break;
        case 2 :
            pd->graphics->getBitmapData(IMG_go, &img_width, &img_height, NULL, NULL, NULL);
            pd->graphics->drawBitmap(IMG_go, (WINDOW_WIDTH - img_width) >> 1, (WINDOW_HEIGHT - img_height) >> 1, kBitmapUnflipped);
            break;
        case 3 :
            GameState = GSGameInit;
            break;
    }
    DrawStatusBar();
    if (Time < pd->system->getCurrentTimeMilliseconds())
    {
        Counter++;
        if(Counter == 1)
        {
            playReadyGoSound();
        }
        if (Counter == 2)
        {
            Time = pd->system->getCurrentTimeMilliseconds() + 400;
        }
        else
            Time = pd->system->getCurrentTimeMilliseconds() + 900;
    }

}

