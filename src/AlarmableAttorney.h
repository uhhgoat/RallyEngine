#pragma once
#include "Alarmable.h"
class AlarmableAttorney
{
public:
	class GameLoop
	{
	private:
		friend class AlarmableManager;
		static void TriggerAlarm(AlarmableManager::AlarmEvent al) { al.first->TriggerAlarm(al.second); };
		static void setStorageRef(AlarmableManager::AlarmEvent al, AlarmableManager::StorageListRef ref) { al.first->RegData->pMyDeleteRef = ref; };
	};
public:
	class Registration
	{
		friend class AlarmRegistrationCommand;
		friend class AlarmDeregistrationCommand;
	private:
		static void AlarmRegistration(AlarmableManager::AlarmEvent al, float t) { al.first->AlarmRegistration(t, al.second); };
		static void AlarmDeregistration(AlarmableManager::AlarmEvent al) { al.first->AlarmDeregistration(al.second); };
	};
};