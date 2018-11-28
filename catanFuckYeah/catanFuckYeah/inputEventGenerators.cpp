#pragma once
#include "inputEventGenerators.h"



mouseEventGenerator::mouseEventGenerator()
{

}

genericEvent* mouseEventGenerator::getEvent()
{

}

timerEventGenerator::timerEventGenerator(double speed)
{
	//al_create_timer(speed);
}
genericEvent *timerEventGenerator::getEvent(void)
{

}

keyboardEventGenerator::keyboardEventGenerator()
{

}

genericEvent* keyboardEventGenerator::getEvent()
{

}