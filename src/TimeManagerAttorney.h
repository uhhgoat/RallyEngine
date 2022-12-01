#pragma once
#include "TimeManager.h"
class TimeManagerAttorney
{
private:
	friend class Rally;
	static void Delete() { TimeManager::Delete(); };
	static void ProcessTime(float sys_time) { TimeManager::privProcessTime(sys_time); }
};