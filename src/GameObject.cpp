#include "GameObject.h"
#include "SceneManager.h"
#include "GameObjectEntryCommand.h"
#include "GameObjectExitCommand.h"

void GameObject::ConnectToScene()
{
	assert(currState == RegistrationState::PENDING_REGISTRATION);

	currState = RegistrationState::CURRENTLY_REGISTERED;
	this->SceneEntry();
	inScene = true;

}
void GameObject::DisconnectFromScene()
{
	if (inScene)
		this->SceneExit();
	currState = RegistrationState::CURRENTLY_DEREGISTERED;

}

void GameObject::SubmitEntry()
{
	assert(currState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(pRegCmd);
	currState = RegistrationState::PENDING_REGISTRATION;
}
void GameObject::SubmitExit()
{
	assert(currState == RegistrationState::CURRENTLY_REGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(pDeregCmd);
	currState = RegistrationState::PENDING_DEREGISTRATION;
}

GameObject::GameObject()
{
	currState = RegistrationState::CURRENTLY_DEREGISTERED;
	pRegCmd = new GameObjectEntryCommand(this);
	pDeregCmd = new GameObjectExitCommand(this);
	inScene = false;
}
GameObject::~GameObject()
{
	delete pRegCmd;
	delete pDeregCmd;
}