
#include "commonController.hpp"

#include "../gfx.hpp"

CommonController::CommonController()
: frameSkip(1)
, inverseFrameSkip(false)
, cycles(0)
{
}

bool CommonController::process()
{
	bool ret = true;

	if(gfx.testAnyInputOnce(AnyBack))
	{
		ret = false;
	}

	int newFrameSkip = 0;
	if(gfx.testAnyInputOnce(AnyNumOne))
		newFrameSkip = 1;
	else if(gfx.testAnyInputOnce(AnyNumTwo))
		newFrameSkip = 2;
	else if(gfx.testAnyInputOnce(AnyNumThree))
		newFrameSkip = 4;
	else if(gfx.testAnyInputOnce(AnyNumFour))
		newFrameSkip = 8;
	else if(gfx.testAnyInputOnce(AnyNumFive))
		newFrameSkip = 16;
	else if(gfx.testAnyInputOnce(AnyNumSix))
		newFrameSkip = 32;
	else if(gfx.testAnyInputOnce(AnyNumSeven))
		newFrameSkip = 64;
	else if(gfx.testAnyInputOnce(AnyNumEight))
		newFrameSkip = 128;
	else if(gfx.testAnyInputOnce(AnyNumNine))
		newFrameSkip = 256;
	else if(gfx.testAnyInputOnce(AnyNumZero))
		newFrameSkip = 512;

	if(newFrameSkip)
	{
		inverseFrameSkip = gfx.testAnyInput(AnyInverse);
		frameSkip = newFrameSkip;
	}

	++cycles;

	return ret;
}
