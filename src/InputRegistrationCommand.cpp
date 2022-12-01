#include "InputRegistrationCommand.h"
#include "InputableAttorney.h"

InputRegistrationCommand::InputRegistrationCommand(Inputable* up, AZUL_KEY key, EVENT_TYPE e)
	:ptrUp(up), myKey(key), myE(e)
{
}

void InputRegistrationCommand::execute()
{
	InputableAttorney::Registration::SceneRegistration(ptrUp, myKey, myE);
}