#include "DeltaTime.h"
#include <time.h>

float DeltaTime::deltaTime()
{
	float nowTime = clock();
	float deltatime = (nowTime - LastTime) / 1000.0f;
	LastTime = clock();
	return deltatime;
}
