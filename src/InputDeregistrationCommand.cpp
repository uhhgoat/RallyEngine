#include "InputDeregistrationCommand.h"
#include "InputableAttorney.h"

InputDeregistrationCommand::InputDeregistrationCommand(Inputable* up, AZUL_KEY key, EVENT_TYPE e)
	:ptrUp(up), myKey(key), myE(e)
{
}

void InputDeregistrationCommand::execute()
{
	InputableAttorney::Registration::SceneDeregistration(ptrUp, myKey, myE);
}