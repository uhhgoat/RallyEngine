#include "Alarmable.h"
#include "SceneManager.h"
#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"
#include <assert.h>

void Alarmable::AlarmRegistration(float t, AlarmableManager::ALARM_ID id)
{
	assert(RegData[id].regStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneManager::GetCurrentScene()->Register(t, AlarmableManager::AlarmEvent(this, id));
	RegData[id].regStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}
void Alarmable::AlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	assert(RegData[id].regStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneManager::GetCurrentScene()->Deregister(RegData[id].pMyDeleteRef);
	RegData[id].regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}
void Alarmable::SubmitAlarmRegistration(float t, AlarmableManager::ALARM_ID id)
{
	assert(RegData[id].regStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	RegData[id].pRegistrationCmd->setTime(t);
	SceneManager::GetCurrentScene()->SubmitCommand(RegData[id].pRegistrationCmd);
	RegData[id].regStateCurr = RegistrationState::PENDING_REGISTRATION;
}
void Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	assert(RegData[id].regStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(RegData[id].pDeregistrationCmd);
	RegData[id].regStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

bool Alarmable::AlarmActive(AlarmableManager::ALARM_ID id)
{
	return RegData[id].regStateCurr == RegistrationState::CURRENTLY_REGISTERED;
}

void Alarmable::TriggerAlarm(AlarmableManager::ALARM_ID id)
{
	RegData[id].regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	switch (id)
	{
	case AlarmableManager::ALARM_0:
		this->Alarm0();
		break;
	case AlarmableManager::ALARM_1:
		this->Alarm1();
		break;
	case AlarmableManager::ALARM_2:
		this->Alarm2();
		break;
	}
}
Alarmable::Alarmable()
{

	RegData[AlarmableManager::ALARM_0].regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	RegData[AlarmableManager::ALARM_0].pRegistrationCmd = new AlarmRegistrationCommand(AlarmableManager::AlarmEvent(this, AlarmableManager::ALARM_0));
	RegData[AlarmableManager::ALARM_0].pDeregistrationCmd = new AlarmDeregistrationCommand(AlarmableManager::AlarmEvent(this, AlarmableManager::ALARM_0));

	RegData[AlarmableManager::ALARM_1].regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	RegData[AlarmableManager::ALARM_1].pRegistrationCmd = new AlarmRegistrationCommand(AlarmableManager::AlarmEvent(this, AlarmableManager::ALARM_1));
	RegData[AlarmableManager::ALARM_1].pDeregistrationCmd = new AlarmDeregistrationCommand(AlarmableManager::AlarmEvent(this, AlarmableManager::ALARM_1));

	RegData[AlarmableManager::ALARM_2].regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	RegData[AlarmableManager::ALARM_2].pRegistrationCmd = new AlarmRegistrationCommand(AlarmableManager::AlarmEvent(this, AlarmableManager::ALARM_2));
	RegData[AlarmableManager::ALARM_2].pDeregistrationCmd = new AlarmDeregistrationCommand(AlarmableManager::AlarmEvent(this, AlarmableManager::ALARM_2));
}
Alarmable::~Alarmable()
{
	//delete RegData;
	delete RegData[AlarmableManager::ALARM_0].pRegistrationCmd;
	delete RegData[AlarmableManager::ALARM_0].pDeregistrationCmd;
	delete RegData[AlarmableManager::ALARM_1].pRegistrationCmd;
	delete RegData[AlarmableManager::ALARM_1].pDeregistrationCmd;
	delete RegData[AlarmableManager::ALARM_2].pRegistrationCmd;
	delete RegData[AlarmableManager::ALARM_2].pDeregistrationCmd;
}