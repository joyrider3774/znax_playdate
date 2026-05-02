#include "gamefuncs.h"
#include "common.h"
#include "defines.h"
#include "state_timeover.h"
#include "cworldparts.h"
#include "sound.h"
#include "state_gethighscorename.h"
#include "pd_api.h"
#include "Pd_helperfuncs.h"

void TimeOverInit()
{
    Time = pd->system->getCurrentTimeMilliseconds() + 1250;
    Counter=0;    
    Timer = 0;
    CWorldParts_DeSelect(World, false);
}

void TimeOver()
{
   
    if (GameState == GSTimeOverInit)
    {
        TimeOverInit();
        GameState = GSTimeOver;
    }
    if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
    {
        playMenuBackSound();
        GameState = GSTitleScreenInit;
    }

    CWorldParts_Draw(World);
    switch(Counter)
    {
        case 0 :
            int timeover_width, timeover_height;
            pd->graphics->getBitmapData(IMG_timeover, &timeover_width, &timeover_height, NULL, NULL, NULL);
            pd->graphics->drawBitmap(IMG_timeover, (WINDOW_WIDTH - timeover_width) >> 1, (WINDOW_HEIGHT - timeover_height) >> 1, kBitmapUnflipped);
            break;
    }
    DrawStatusBar();
    if (Time < pd->system->getCurrentTimeMilliseconds())
    {
        GameState = GSGetHighScoreNameInit;
    }
}

