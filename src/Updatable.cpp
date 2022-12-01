#include "Updatable.h"
#include "SceneManager.h"
#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"
#include <assert.h>

void Updatable::SceneRegistration()
{
	assert(regStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneManager::GetCurrentScene()->Register(this);
	regStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}
void Updatable::SceneDeregistration()
{
	assert(regStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneManager::GetCurrentScene()->Deregister(pMyDeleteRef);
	regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}
void Updatable::SubmitUpdateRegistration()
{
	assert(regStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(pRegistrationCmd);
	regStateCurr = RegistrationState::PENDING_REGISTRATION;
}
void Updatable::SubmitUpdateDeregistration()
{
	assert(regStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(pDeregistrationCmd);
	regStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}
Updatable::Updatable()
{
	regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	pRegistrationCmd = new UpdateRegistrationCommand(this);
	pDeregistrationCmd = new UpdateDeregistrationCommand(this);
}
Updatable::~Updatable()
{
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
}