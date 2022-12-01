#pragma once
#include "CommandBase.h"
#include "EventType.h"
#include "AzulCore.h"
class Inputable;
class InputRegistrationCommand : public CommandBase
{
public:
	Inputable* ptrUp;
	AZUL_KEY myKey;
	EVENT_TYPE myE;
	InputRegistrationCommand(Inputable* up, AZUL_KEY key, EVENT_TYPE e);
	void execute();
private:
};