#pragma once
#include "Updatable.h"
class UpdatableAttorney
{
public:
	class GameLoop
	{
	private:
		friend class UpdatableManager;
		static void Update(Updatable* pMgr) { pMgr->Update(); };
		static void setStorageRef(Updatable* pMgr, UpdatableManager::StorageListRef ref) { pMgr->pMyDeleteRef = ref; };
	};
public:
	class Registration
	{
	private:
		friend class UpdateRegistrationCommand;
		friend class UpdateDeregistrationCommand;
		static void SceneRegistration(Updatable* pMgr) { pMgr->SceneRegistration(); };
		static void SceneDeregistration(Updatable* pMgr) { pMgr->SceneDeregistration(); };
	};
};