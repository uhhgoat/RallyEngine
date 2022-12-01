#include "AlarmRegistrationCommand.h"
#include "AlarmableAttorney.h"
AlarmRegistrationCommand::AlarmRegistrationCommand(AlarmableManager::AlarmEvent alm)
	:ptrAlm(alm)
{
	time = 0.0f;
}
void AlarmRegistrationCommand::execute()
{
	AlarmableAttorney::Registration::AlarmRegistration(ptrAlm, time);
}
void AlarmRegistrationCommand::setTime(float t)
{
	time = t;
}