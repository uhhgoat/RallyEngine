#pragma once
#include "FreezeTime.h"
class TimeManager
{
public:
	friend class Rally;
	static float GetTime() { return Instance().privGetTime(); };
	static float GetFrameTime() { return Instance().privGetFrameTime(); };
	friend class TimeManagerAttorney;
private:
	static void Delete();
	FreezeTime FrzTime;
	float previousTime = 0;
	float currentTime = 0;
	float frameTime = 0;
	static TimeManager* ptrInstance;
	TimeManager() = default;
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	~TimeManager();

	static TimeManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TimeManager;
		return *ptrInstance;
	};

	static void privProcessTime(float sys_time);

	float privGetTime();
	float privGetFrameTime();
};
