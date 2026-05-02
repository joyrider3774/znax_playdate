#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include "gamefuncs.h"
#include "defines.h"
#include "common.h"
#include "sound.h"
#include "state_showhighscores.h"
#include "Pd_helperfuncs.h"
#include "pd_api.h"

int ScoreType;
    
void ShowHighScoresInit()
{
    ScoreType = GameType;
}

void ShowHighScores()
{
    if (GameState == GSShowHighScoresInit)
    {
        ShowHighScoresInit();
        GameState = GSShowHighScores;
    }

    LCDColor TextColor = kColorBlack;
    int Teller = 0;
    char *Text;
    if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
    {
        
        if (ScoreType == Fixed)
        {
            playMenuAcknowlege();
            ScoreType = Relative;
        }
        else
        {
            playMenuBackSound();
            GameState = GSTitleScreenInit;
        }
    }
    if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
    {
        playMenuBackSound();
        GameState = GSTitleScreenInit;
    }
    pd->graphics->drawBitmap(IMG_highscores, 0, 0, kBitmapUnflipped);
    switch(ScoreType)
    {
        case Fixed :
            pd->system->formatString(&Text,"%s", "Fixed Timer");
            break;
        case Relative :
            pd->system->formatString(&Text,"%s", "Relative Timer");
            break;
    }

    int tw = pd->graphics->getTextWidth(font, Text, strlen(Text), kASCIIEncoding, 0);
    drawTextColor(true,NULL, font, Text, strlen(Text),kASCIIEncoding,(WINDOW_WIDTH - tw) >> 1,227,TextColor, false);
    
    pd->system->realloc(Text, 0);

    for(Teller = 0;Teller<10;Teller++)
    {
        pd->system->formatString(&Text,"%2d.%s",Teller+1,saveData.HighScores[ScoreType][Teller].PName);
        drawTextColor(true, NULL, font, Text, strlen(Text), kASCIIEncoding, 50,66+Teller*16, TextColor, false);
        pd->system->realloc(Text, 0);

        pd->system->formatString(&Text,"%07ld",saveData.HighScores[ScoreType][Teller].PScore);
        drawTextColor(true, NULL, font, Text, strlen(Text), kASCIIEncoding, 220, 66 + Teller * 16, TextColor, false);
        pd->system->realloc(Text, 0);
    }
}
