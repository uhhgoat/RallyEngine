#include "Collidable.h"
class CollidableAttorney
{
public:
	class Registration
	{
		friend class CollisionRegistrationCommand;
		friend class CollisionDeregistrationCommand;
		friend class CollidableGroup;
	private:
		static void SceneRegistration(Collidable* pMgr) { pMgr->SceneRegistration(); };
		static void SceneDeregistration(Collidable* pMgr) { pMgr->SceneDeregistration(); };

		static void setStorageRef(Collidable* pMgr, CollidableGroup::StorageListRef ref) { pMgr->pMyDeleteRef = ref; };
	};
};