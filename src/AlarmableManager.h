#pragma once
#include <map>
class Alarmable;
class AlarmableManager
{
public:
	enum ALARM_ID
	{
		ALARM_0,
		ALARM_1,
		ALARM_2
	};
	using AlarmEvent = std::pair < Alarmable*, ALARM_ID>;

	void ReduceTimeBy(float seconds, AlarmableManager::ALARM_ID id);
	void AddTime(float seconds, AlarmableManager::ALARM_ID id);

private:

	using StorageList = std::multimap<AlarmEvent, float>;
	StorageList storageList;


public:
	using StorageListRef = StorageList::iterator;

	static const int ALARM_NUMBER = 3;
	void Register(float t, AlarmEvent al);
	void Deregister(const StorageListRef ref);
	void ProcessAlarms();

	AlarmableManager() = default;
	~AlarmableManager();
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator=(const AlarmableManager&) = delete;
};