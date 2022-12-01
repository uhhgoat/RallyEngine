#pragma once
#include "Inputable.h"
class InputableAttorney
{
public:
	class GameLoop
	{
	private:
		friend class SingleKeyEventManager;
		static void setStorageRef(Inputable* pMgr, EVENT_TYPE e, AZUL_KEY k, SingleKeyEventManager::StorageListRef ref) { pMgr->setStorageRef(e, k, ref); };
	};
public:
	class Registration
	{
		friend class InputRegistrationCommand;
		friend class InputDeregistrationCommand;
	private:
		static void SceneRegistration(Inputable* pMgr, AZUL_KEY k, EVENT_TYPE e) { pMgr->SceneRegistration(k, e); };
		static void SceneDeregistration(Inputable* pMgr, AZUL_KEY k, EVENT_TYPE e) { pMgr->SceneDeregistration(k, e); };
	};
};