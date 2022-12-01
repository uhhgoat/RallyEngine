#pragma once
#include "CommandBase.h"
#include "Alarmable.h"
class AlarmRegistrationCommand : public CommandBase
{
public:
	AlarmableManager::AlarmEvent ptrAlm;
	float time;
	void execute();
	AlarmRegistrationCommand(AlarmableManager::AlarmEvent alm);
	void setTime(float t);
private:
};