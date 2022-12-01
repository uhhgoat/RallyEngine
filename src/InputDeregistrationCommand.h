#pragma once
#include "CommandBase.h"
#include "EventType.h"
#include "AzulCore.h"
class Inputable;
class InputDeregistrationCommand : public CommandBase
{
public:
	Inputable* ptrUp;
	AZUL_KEY myKey;
	EVENT_TYPE myE;
	InputDeregistrationCommand(Inputable* up, AZUL_KEY key, EVENT_TYPE e);
	void execute();
private:
};