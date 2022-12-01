#include "Drawable.h"
#include "SceneManager.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"
#include <assert.h>

void Drawable::SceneRegistration()
{
	assert(regStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneManager::GetCurrentScene()->Register(this);
	regStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}
void Drawable::SceneDeregistration()
{
	assert(regStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneManager::GetCurrentScene()->Deregister(pMyDeleteRef);
	regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}
void Drawable::SubmitDrawRegistration()
{
	assert(regStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(pRegistrationCmd);
	regStateCurr = RegistrationState::PENDING_REGISTRATION;
}
void Drawable::SubmitDrawDeregistration()
{
	assert(regStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(pDeregistrationCmd);
	regStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}
Drawable::Drawable()
{
	regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	pRegistrationCmd = new DrawRegistrationCommand(this);
	pDeregistrationCmd = new DrawDeregistrationCommand(this);
}
Drawable::~Drawable()
{
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
}