#pragma once
class DeltaTime
{
public:
	float deltaTime();
private:
	float deltatime = 0;
	float LastTime = 0;
};

