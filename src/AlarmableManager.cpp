#include "AlarmableManager.h"
#include "AlarmableAttorney.h"
#include "Rally.h"
#include "TimeManager.h"
AlarmableManager::~AlarmableManager()
{
}

void AlarmableManager::ProcessAlarms()
{
	std::multimap<AlarmEvent, float>::iterator it;
	it = storageList.begin();
	while(it != storageList.end() && (*it).second <= TimeManager::GetTime())
	{
			AlarmableAttorney::GameLoop::TriggerAlarm((*it).first);
			it = storageList.erase(it);
	}
}

void AlarmableManager::ReduceTimeBy(float seconds, AlarmableManager::ALARM_ID id)
{
	std::multimap<AlarmEvent, float>::iterator it;
	it = storageList.begin();
	while (it != storageList.end())
	{
		if ((*it).first.second == id)
		{
			(*it).second -= seconds;
		}
		it++;
	}
}
void AlarmableManager::AddTime(float seconds, AlarmableManager::ALARM_ID id)
{
	std::multimap<AlarmEvent, float>::iterator it;
	it = storageList.begin();
	while (it != storageList.end())
	{
		if ((*it).first.second == id)
		{
			(*it).second += seconds;
		}
		it++;
	}
}

void AlarmableManager::Register(float t, AlarmEvent alm)
{
	float triggerTime = TimeManager::GetTime() + t;
	AlarmableManager::StorageListRef ref = storageList.insert(std::pair<AlarmEvent, float>(alm, triggerTime));
	AlarmableAttorney::GameLoop::setStorageRef(alm, ref);
}

void AlarmableManager::Deregister(AlarmableManager::StorageListRef ref)
{
	storageList.erase(ref);
}
