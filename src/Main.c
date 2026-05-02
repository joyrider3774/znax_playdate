#include "pd_api.h"
#include "defines.h"
#include "znax.h"
#include "Common.h"
#include "Pd_helperfuncs.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg)
{

	if ( event == kEventInit )
	{
		setPDPtr(playdate);		
		setupGame();
		playdate->display->setRefreshRate(FPS);
		playdate->system->setUpdateCallback(mainLoop, NULL);
	}

	if (event == kEventTerminate)
	{
		terminateGame();
	}
	
	return 0;
}
