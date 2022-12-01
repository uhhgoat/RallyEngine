#include "AlarmDeregistrationCommand.h"
#include "AlarmableAttorney.h"
AlarmDeregistrationCommand::AlarmDeregistrationCommand(AlarmableManager::AlarmEvent alm)
	:ptrAlm(alm)
{

}
void AlarmDeregistrationCommand::execute()
{
	AlarmableAttorney::Registration::AlarmDeregistration(ptrAlm);
}