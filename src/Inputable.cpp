#include "Inputable.h"
#include "SceneManager.h"
#include "InputRegistrationCommand.h"
#include "InputDeregistrationCommand.h"
void Inputable::SceneRegistration(AZUL_KEY k, EVENT_TYPE e)
{
	RegistrationData regdata;
	switch (e)
	{
	case EVENT_TYPE::KEY_PRESS:
		assert(pCmdsPress.at(k).regStateCurr == RegistrationState::PENDING_REGISTRATION);
		SceneManager::GetCurrentScene()->Register(this, k, e);
		pCmdsPress.at(k).regStateCurr = RegistrationState::CURRENTLY_REGISTERED;
		break;
	case EVENT_TYPE::KEY_RELEASE:
		assert(pCmdsRelease.at(k).regStateCurr == RegistrationState::PENDING_REGISTRATION);
		SceneManager::GetCurrentScene()->Register(this, k, e);
		pCmdsRelease.at(k).regStateCurr = RegistrationState::CURRENTLY_REGISTERED;
		break;
	case EVENT_TYPE::KEY_DOWN:
		assert(pCmdsDown.at(k).regStateCurr == RegistrationState::PENDING_REGISTRATION);
		SceneManager::GetCurrentScene()->Register(this, k, e);
		pCmdsDown.at(k).regStateCurr = RegistrationState::CURRENTLY_REGISTERED;
		break;
	default:
		break;
	};

}
void Inputable::SceneDeregistration(AZUL_KEY k, EVENT_TYPE e)
{
	RegistrationData regdata;
	switch (e)
	{
	case EVENT_TYPE::KEY_PRESS:
		assert(pCmdsPress.at(k).regStateCurr == RegistrationState::PENDING_DEREGISTRATION);
		SceneManager::GetCurrentScene()->Deregister(pCmdsPress.at(k).pMyDeleteRef, k, e);
		pCmdsPress.at(k).regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
		break;
	case EVENT_TYPE::KEY_RELEASE:
		assert(pCmdsRelease.at(k).regStateCurr == RegistrationState::PENDING_DEREGISTRATION);
		SceneManager::GetCurrentScene()->Deregister(pCmdsRelease.at(k).pMyDeleteRef, k, e);
		pCmdsRelease.at(k).regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
		break;
	case EVENT_TYPE::KEY_DOWN:
		assert(pCmdsDown.at(k).regStateCurr == RegistrationState::PENDING_DEREGISTRATION);
		SceneManager::GetCurrentScene()->Deregister(pCmdsDown.at(k).pMyDeleteRef, k, e);
		pCmdsDown.at(k).regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
		break;
	default:
		break;
	};

}
void Inputable::SubmitKeyRegistration(AZUL_KEY k, EVENT_TYPE e)
{
	if (e == EVENT_TYPE::KEY_PRESS && pCmdsPress.find(k) == pCmdsPress.end())
	{
		RegistrationData regdata;
		regdata.regStateCurr = RegistrationState::PENDING_REGISTRATION;
		regdata.pRegistrationCmd = new InputRegistrationCommand(this, k, e);
		regdata.pDeregistrationCmd = new InputDeregistrationCommand(this, k, e);
		pCmdsPress.insert(std::pair<AZUL_KEY, RegistrationData>(k, regdata));
		SceneManager::GetCurrentScene()->SubmitCommand(regdata.pRegistrationCmd);
	}
	else if (e == EVENT_TYPE::KEY_RELEASE && pCmdsRelease.find(k) == pCmdsRelease.end())
	{
		RegistrationData regdata;
		regdata.regStateCurr = RegistrationState::PENDING_REGISTRATION;
		regdata.pRegistrationCmd = new InputRegistrationCommand(this, k, e);
		regdata.pDeregistrationCmd = new InputDeregistrationCommand(this, k, e);
		pCmdsRelease.insert(std::pair<AZUL_KEY, RegistrationData>(k, regdata));
		SceneManager::GetCurrentScene()->SubmitCommand(regdata.pRegistrationCmd);
	}
	else if (e == EVENT_TYPE::KEY_DOWN && pCmdsDown.find(k) == pCmdsDown.end())
	{
		RegistrationData regdata;
		regdata.regStateCurr = RegistrationState::PENDING_REGISTRATION;
		regdata.pRegistrationCmd = new InputRegistrationCommand(this, k, e);
		regdata.pDeregistrationCmd = new InputDeregistrationCommand(this, k, e);
		pCmdsDown.insert(std::pair<AZUL_KEY, RegistrationData>(k, regdata));
		SceneManager::GetCurrentScene()->SubmitCommand(regdata.pRegistrationCmd);
	}
}
void Inputable::SubmitKeyDeregistration(AZUL_KEY k, EVENT_TYPE e)
{
	if (e == EVENT_TYPE::KEY_PRESS)
	{
		assert(pCmdsPress.at(k).regStateCurr == RegistrationState::CURRENTLY_REGISTERED);
		SceneManager::GetCurrentScene()->SubmitCommand(pCmdsPress.at(k).pDeregistrationCmd);
		pCmdsPress.at(k).regStateCurr = RegistrationState::PENDING_DEREGISTRATION;
	}
	else if (e == EVENT_TYPE::KEY_RELEASE)
	{
		assert(pCmdsRelease.at(k).regStateCurr == RegistrationState::CURRENTLY_REGISTERED);
		SceneManager::GetCurrentScene()->SubmitCommand(pCmdsRelease.at(k).pDeregistrationCmd);
		pCmdsRelease.at(k).regStateCurr = RegistrationState::PENDING_DEREGISTRATION;
	}
	else if (e == EVENT_TYPE::KEY_DOWN)
	{
		assert(pCmdsDown.at(k).regStateCurr == RegistrationState::CURRENTLY_REGISTERED);
		SceneManager::GetCurrentScene()->SubmitCommand(pCmdsDown.at(k).pDeregistrationCmd);
		pCmdsDown.at(k).regStateCurr = RegistrationState::PENDING_DEREGISTRATION;
	}
}
void Inputable::setStorageRef(EVENT_TYPE e, AZUL_KEY k, SingleKeyEventManager::StorageListRef ref)
{
	
	switch (e)
	{
	case EVENT_TYPE::KEY_PRESS:
		pCmdsPress.at(k).pMyDeleteRef = ref;
		break;
	case EVENT_TYPE::KEY_RELEASE:
		pCmdsRelease.at(k).pMyDeleteRef = ref;
		break;
	case EVENT_TYPE::KEY_DOWN:
		pCmdsDown.at(k).pMyDeleteRef = ref;
		break;
	default:
		break;
	};
	
}
Inputable::Inputable()
{
	
}
Inputable::~Inputable()
{
	//delete all entities.
	
	for (std::map<AZUL_KEY, RegistrationData>::iterator it = pCmdsPress.begin(); it != pCmdsPress.end(); it++)
	{
		delete it->second.pRegistrationCmd;
		delete it->second.pDeregistrationCmd;
	}
	for (std::map<AZUL_KEY, RegistrationData>::iterator it = pCmdsRelease.begin(); it != pCmdsRelease.end(); it++)
	{
		delete it->second.pRegistrationCmd;
		delete it->second.pDeregistrationCmd;
	}
	for (std::map<AZUL_KEY, RegistrationData>::iterator it = pCmdsDown.begin(); it != pCmdsDown.end(); it++)
	{
		delete it->second.pRegistrationCmd;
		delete it->second.pDeregistrationCmd;
	}
}