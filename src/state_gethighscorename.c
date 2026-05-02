#include <stdio.h>
#include <stdlib.h>
#include "gamefuncs.h"
#include "defines.h"
#include "common.h"
#include "state_gethighscorename.h"
#include "sound.h"
#include "Pd_helperfuncs.h"
#include "pd_api.h"

char Name[MAXLENHISCORENAME+1];
bool NameEnd=false,NameSubmitChanges=false;
int NameMaxSelection=0, NameSelection = 0,asci=97;
int ScorePlace;

void GetHighScoreNameInit()
{
	ScorePlace = -1;
	for(int Teller1 =0;Teller1<10;Teller1++)
	{
		if(saveData.HighScores[GameType][Teller1].PScore < Score)
		{
			ScorePlace = Teller1;
			break;          
		}
	}

	if (ScorePlace == -1)
	{
		GameState = GSShowHighScoresInit;
		return;
	}
	NameEnd=false;
	NameSubmitChanges=false;
	NameMaxSelection=0;
	NameSelection = 0;
	asci=97;
	memset(Name, 0, (MAXLENHISCORENAME+1) * sizeof(char));
	NameMaxSelection = 0;
	Name[NameMaxSelection]=chr(asci);
}

void GetHighScoreName()
{
	char NameIn[21];
	if(GameState == GSGetHighScoreNameInit)
	{
		GetHighScoreNameInit();
		if(GameState == GSShowHighScoresInit)
			return;
		GameState = GSGetHighScoreName;
	}

	char* Tekst;
	if ((currButtons & kButtonLeft) && !(prevButtons & kButtonLeft))
	{
		if (NameSelection > 0)
		{	NameSelection--;
			asci = ord(Name[NameSelection]);
			playMenuBackSound();
		}
	}
	if ((currButtons & kButtonRight) && !(prevButtons & kButtonRight))
	{
		if (NameSelection < MAXLENHISCORENAME)
		{
			NameSelection++;
			if (NameSelection > NameMaxSelection)
			{
				Name[NameSelection] = chr(97);
				Name[NameSelection+1] = '\0';
				NameMaxSelection=NameSelection;
			}
			asci = ord(Name[NameSelection]);
			playMenuSelectSound();
		}
	}
	if ((currButtons & kButtonUp) && !(prevButtons & kButtonUp))
	{
		asci++;
		if (asci==123)
		{
			asci=32;
		}
		if (asci==33)
		{
			(asci=48);
		}
		if (asci==58)
		{
			asci=97;
		}
		Name[NameSelection] = chr(asci);
	}
	if ((currButtons & kButtonDown) && !(prevButtons & kButtonDown))
	{
		asci--;
		if(asci==96)
		{
			asci=57;
		}
		if(asci==47)
		{
			asci=32;
		}
		if(asci==31)
		{
			asci=122;
		}
		Name[NameSelection] = chr(asci);
	}
	if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
	{
		playMenuAcknowlege();
		NameEnd = true;
		NameSubmitChanges=true;
	}
	if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
	{
		playMenuBackSound();
		NameEnd=true;
		NameSubmitChanges=false;
	}
	pd->graphics->drawBitmap(IMG_highscores, 0, 0, kBitmapUnflipped);
	char *Msg;
	for(int Teller = 0;Teller<9;Teller++)
	{
		if(Teller < ScorePlace)
		{
			pd->system->formatString(&Msg,"%2d.%s",Teller+1,saveData.HighScores[GameType][Teller].PName);
			drawTextColor(true, NULL, font,Msg,strlen(Msg),kASCIIEncoding, 50,66+Teller*16,kColorBlack, false);
			pd->system->realloc(Msg, 0);
			pd->system->formatString(&Msg,"%07ld",saveData.HighScores[GameType][Teller].PScore);
			drawTextColor(true, NULL, font, Msg, strlen(Msg), kASCIIEncoding, 220, 66 + Teller * 16, kColorBlack, false);
			pd->system->realloc(Msg, 0);
		}
		else
		{
			pd->system->formatString(&Msg,"%2d.%s",Teller+2,saveData.HighScores[GameType][Teller].PName);
			drawTextColor(true, NULL, font, Msg, strlen(Msg), kASCIIEncoding, 50, 66 + (Teller +1)* 16, kColorBlack, false);
			pd->system->realloc(Msg, 0);
			pd->system->formatString(&Msg,"%07ld",saveData.HighScores[GameType][Teller].PScore);
			drawTextColor(true, NULL, font, Msg, strlen(Msg), kASCIIEncoding, 220, 66 + (Teller + 1) * 16, kColorBlack, false);
			pd->system->realloc(Msg, 0);
		}
	}
	pd->system->formatString(&Msg,"%2d.%s",ScorePlace+1,Name);
	drawTextColor(true, NULL, font, Msg, strlen(Msg), kASCIIEncoding, 50, 66 + ScorePlace * 16, (LCDColor)kColorGrey, false);
	pd->system->realloc(Msg, 0);
	pd->system->formatString(&Msg,"%07ld",Score);
	drawTextColor(true, NULL, font, Msg, strlen(Msg), kASCIIEncoding, 220, 66 + ScorePlace * 16, (LCDColor)kColorGrey, false);
	pd->system->realloc(Msg, 0);

	pd->system->formatString(&Tekst,"%s", "USE UP,DOWN,LEFT,RIGHT A=Ok B=Cancel" );
	int tw = pd->graphics->getTextWidth(font, Tekst, strlen(Tekst), kASCIIEncoding, 0);
	drawTextColor(true, NULL, font, Tekst, strlen(Tekst), kASCIIEncoding, (WINDOW_WIDTH - tw) >> 1, 227, kColorBlack, false);
	pd->system->realloc(Tekst, 0);

	if(NameEnd)
	{
		GameState = GSShowHighScoresInit;
	}

	if(GameState != GSGetHighScoreName)
	{
		Name[NameMaxSelection+1] = '\0';
		while ((Name[0] == ' ') && (NameMaxSelection>-1))
		{
			for (int Teller=0;Teller<NameMaxSelection;Teller++)
				Name[Teller] = Name[Teller+1];
			NameMaxSelection--;
		}
		if (NameMaxSelection>-1)
			while ((Name[NameMaxSelection] == ' ') && (NameMaxSelection>0))
			{
				Name[NameMaxSelection] = '\0';
				NameMaxSelection--;
			}

		memset(NameIn, 0, (MAXLENHISCORENAME+1) * sizeof(char));
		if (!NameSubmitChanges)
		{
			strcpy(NameIn," ");
		}
		else
		{
	        strcpy(NameIn,Name);
		}

		for(int Teller2=8;Teller2>=ScorePlace;Teller2--)
  			saveData.HighScores[GameType][Teller2+1] = saveData.HighScores[GameType][Teller2];
        if((strcmp(NameIn," ") == 0))
        	strcpy(saveData.HighScores[GameType][ScorePlace].PName,"player");
        else
            strcpy(saveData.HighScores[GameType][ScorePlace].PName,NameIn);
        saveData.HighScores[GameType][ScorePlace].PScore = Score;
		SaveHighScores();
	}
}
