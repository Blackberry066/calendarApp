#include "Display.h"


void Display::setMinMax(const int someDaysCount, const int direction)	{
        if (direction == 0) {
        	minTime = *localtime(&displayTime);
        	displayTime+=someDaysCount*secondsPerDay;
        	maxTime = *localtime(&displayTime);
        }
        else {
        	maxTime = *localtime(&displayTime);
        	displayTime-=someDaysCount*secondsPerDay;
        	minTime = *localtime(&displayTime);
        }  
        minTime.tm_year+=1900;
        minTime.tm_mon+=1;
        maxTime.tm_year+=1900;
        maxTime.tm_mon+=1;

    }
