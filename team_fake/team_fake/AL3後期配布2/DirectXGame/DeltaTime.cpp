#include "DeltaTime.h"
#include <chrono>

std::chrono::system_clock::time_point  LastTime;
std::chrono::system_clock::time_point  Last;
float DeltaTime::deltaTime()
{
	auto nowTime = std::chrono::system_clock::now();
	auto dur = nowTime - LastTime;
	auto deltatime = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	LastTime = nowTime;
	return deltatime / 1000.0f;
}
