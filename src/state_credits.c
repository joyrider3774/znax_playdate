#include "defines.h"
#include "gamefuncs.h"
#include "common.h"
#include "state_credits.h"
#include "sound.h"
#include "Pd_helperfuncs.h"
#include "pd_api.h"

void CreditsInit()
{

}

void Credits()
{
    if (GameState == GSCreditsInit)
    {
        CreditsInit();
        GameState = GSCredits;
    }
    
    if (((currButtons & kButtonA) && !(prevButtons & kButtonA)) ||
        ((currButtons & kButtonB) && !(prevButtons & kButtonB)))
    {
        GameState = GSTitleScreenInit;
        playMenuBackSound();
    }
    
    pd->graphics->drawBitmap(IMG_titlescreen, 0, 0, kBitmapUnflipped);
    pd->graphics->drawBitmap(IMG_credits, 48, 76, kBitmapUnflipped);
}
