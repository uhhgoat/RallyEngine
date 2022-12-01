#pragma once
#include "CommandBase.h"
#include "Alarmable.h"
class AlarmDeregistrationCommand : public CommandBase
{
public:
	AlarmableManager::AlarmEvent ptrAlm;
	void execute();
	AlarmDeregistrationCommand(AlarmableManager::AlarmEvent alm);
private:
};