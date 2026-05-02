#include "gamefuncs.h"
#include "common.h"
#include "defines.h"
#include "state_intro.h"
#include "Pd_helperfuncs.h"
#include "pd_api.h"
#include "sound.h"

int IntroScreenNr;

void IntroInit()
{
    IntroScreenNr = 1;
    Time = pd->system->getCurrentTimeMilliseconds();
}

void Intro()
{
    if(GameState == GSIntroInit)
    {
        IntroInit();
        GameState = GSIntro;
    }
    if(((currButtons & kButtonA) && !(prevButtons & kButtonA)) ||
        ((currButtons & kButtonB) && !(prevButtons & kButtonB)))
    {
        GameState = GSTitleScreenInit;
        playWelcomeSound();
    }

     
    switch(IntroScreenNr)
    {
        case 1 :
            pd->graphics->drawBitmap(IMG_intro1, 0, 0, kBitmapUnflipped);
            break;
        case 2 :
            pd->graphics->drawBitmap(IMG_intro2, 0, 0, kBitmapUnflipped);
            break;
    }

    if(Time + 3700 < pd->system->getCurrentTimeMilliseconds())
    {
        IntroScreenNr++;
        if (IntroScreenNr > 2)
        {
            GameState = GSTitleScreenInit;
            playWelcomeSound();
        }
        Time = pd->system->getCurrentTimeMilliseconds();
    }

}
