#include "TimeManager.h"
#include "Rally.h"

TimeManager* TimeManager::ptrInstance = nullptr;


void TimeManager::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

TimeManager::~TimeManager()
{

}

float TimeManager::privGetTime()
{
	return Instance().currentTime;
}
float TimeManager::privGetFrameTime()
{
	return Instance().frameTime;
}

void TimeManager::privProcessTime(float sys_time)
{
	Instance().previousTime = Instance().currentTime;
	Instance().currentTime = Instance().FrzTime.GetTimeInSeconds(sys_time);
	Instance().frameTime = Instance().currentTime - Instance().previousTime;
}
