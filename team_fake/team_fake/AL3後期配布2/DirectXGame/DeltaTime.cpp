#include "DeltaTime.h"
#include <time.h>

float DeltaTime::deltaTime()
{
	float nowTime = clock();
	deltatime = (nowTime - LastTime) / 1000.0f;
	LastTime = clock();
	return deltatime;
}
