#ifndef Collidable_H
#define Collidable_H
#pragma once
#include "SceneManager.h"
#include "CollidableGroup.h"
#include "RegistrationState.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
class Collidable
{
private:

	friend class CollidableAttorney;
	CollisionManager::TypeID myID = CollisionManager::ID_UNDEFINED;

	void SceneRegistration();
	void SceneDeregistration();

	CollisionVolume* colVolume;
	Model* pColModel;

	CollisionVolumeBSphere* defaultBSphere;


	CollidableGroup::StorageListRef pMyDeleteRef;
	RegistrationState regStateCurr;
	CollisionRegistrationCommand* pRegistrationCmd;
	CollisionDeregistrationCommand* pDeregistrationCmd;

protected:
	/*!
	\brief Called when setting the object type to register collision.\n

	\par Example:
	\code
	Player::Player()
	{
		SetCollidableGroup<PlayerTank>();
	}
	\endcode
	*/
	template < typename C>
	void SetCollidableGroup()
	{
		myID = SceneManager::GetCurrentScene()->GetCollisionMgr()->GetTypeID<C>();
	}

public:
	Collidable();
	virtual ~Collidable();
	Collidable(const Collidable&) = delete;
	Collidable& operator=(const Collidable&) = delete;

	/*!
	\brief Types of collision volume that can be set on a GameObject.
	*/
	enum VolumeType
	{
		BSPHERE,
		AABB,
		OBB
	};

	/*!
	\brief Called when registering and object to be have collision events.\n

	\par Example:
	\code
	Player::Player()
	{
		SubmitCollisionRegistration();
	}
	\endcode
	*/
	void SubmitCollisionRegistration();
	/*!
	\brief Called when deregistering and object from having collision events.

	\par Example:
	\code
	Player::~Player()
	{
		SubmitCollisionDeregistration();
	}
	\endcode
	*/
	void SubmitCollisionDeregistration();
	/*!
	\brief To be implemented by derived class and define what to happen on each collision event.

	\par Example:
	\code
	void Player::Collision(Bullet* bullet)
	{
		AZUL_UNUSED(bullet);
		DebugMsg::out("PlayerTank Collision with Bullet \n");
		TakeDamage();
	}
	\endcode
	*/
	void Collision(Collidable* col);
	virtual void CollisionTerrain();

	/*!
	\brief Called to get the current collision volume of Collidable.
	*/
	const CollisionVolume& GetCollisionVolume();

	/*!
	\brief Called to get the default Bounding Sphere volume used for collision testing.
	*/
	const CollisionVolumeBSphere& GetDefaultBSphere();

	/*!
	\brief Called when setting the collision body of an object.\n

	\par Example:
	\code
	Player::Player()
	{
		SetColliderModel(pGObj_Tank->getModel(), Collidable::VolumeType::BSPHERE);
	}
	\endcode
	*/
	void SetColliderModel(Model* mod, VolumeType vt);
	/*!
	\brief Called when updating the collision body of an object.\n

	\par Example:
	\code
	void Player::Update()
	{
		Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
		this->UpdateCollisionData(world, scale);
	}
	\endcode
	*/
	void UpdateCollisionData(Matrix& mat, float scale);
};
#endif