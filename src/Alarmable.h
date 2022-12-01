#pragma once
#include "AlarmableManager.h"
#include "RegistrationState.h"
class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;

class Alarmable
{
public:

	friend class AlarmableAttorney;

	Alarmable();
	~Alarmable();
	Alarmable(const Alarmable&) = delete;
	Alarmable& operator=(const Alarmable&) = delete;

protected:
	/*!
	\brief Called when registering and object to have a timer countdown to an event.
	The first parameter specifies the time in seconds until the alarm triggers, the second is which alarm to trigger.

	\par Example:
	\code
	Player::Player()
	{
		Alarmable::SubmitAlarmRegistration(3, AlarmableManager::ALARM_0);
	}
	\endcode
	*/
	void SubmitAlarmRegistration(float t, AlarmableManager::ALARM_ID id);
	/*!
	\brief Called when deregistering and object from an existing active alarm.
	The parameter indicated which alarm to cancel.

	\par Example:
	\code
	Player::~Player()
	{
		Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	}
	\endcode
	*/
	void SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id);

	bool AlarmActive(AlarmableManager::ALARM_ID id);

private:
	/*!
	\brief To be implemented in derived class to define what to do when the alarm triggers.

	\par Example:
	\code
	void Bullet::Alarm0()
	{
		SubmitExit();
	}
	\endcode
	*/
	virtual void Alarm0() {};
	virtual void Alarm1() {};
	virtual void Alarm2() {};

	struct RegistrationData
	{
		AlarmableManager::StorageListRef pMyDeleteRef;
		RegistrationState regStateCurr;
		AlarmRegistrationCommand* pRegistrationCmd;
		AlarmDeregistrationCommand* pDeregistrationCmd;
	};


	RegistrationData RegData[AlarmableManager::ALARM_NUMBER];

	void AlarmRegistration(float t, AlarmableManager::ALARM_ID id);
	void AlarmDeregistration(AlarmableManager::ALARM_ID id);
	void TriggerAlarm(AlarmableManager::ALARM_ID id);

};
