#pragma once
#include "Drawable.h"
class DrawableAttorney
{
public:
	class GameLoop
	{
	private:
		friend class DrawableManager;
		static void Draw(Drawable* pMgr) { pMgr->Draw(); };
		static void Draw2D(Drawable* pMgr) { pMgr->Draw2D(); };
		static void setStorageRef(Drawable* pMgr, DrawableManager::StorageListRef ref) { pMgr->pMyDeleteRef = ref; };
	};
	class Registration
	{
	private:
		friend class DrawRegistrationCommand;
		friend class DrawDeregistrationCommand;
		static void SceneRegistration(Drawable* pMgr) { pMgr->SceneRegistration(); };
		static void SceneDeregistration(Drawable* pMgr) { pMgr->SceneDeregistration(); };
	};

};