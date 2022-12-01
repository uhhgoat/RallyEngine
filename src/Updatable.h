#pragma once
#include "UpdatableManager.h"
#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"
#include "RegistrationState.h"
class Updatable
{
	
	friend class UpdatableAttorney;

public:
	Updatable();
	virtual ~Updatable();
	Updatable(const Updatable&) = delete;
	Updatable& operator=(const Updatable&) = delete;
protected:
	/*!
	\brief Called when registering and object to be updated every frame.

	\par Example:
	\code
	Player::Player()
	{
		SubmitUpdateRegistration();
	}
	\endcode
	*/
	void SubmitUpdateRegistration();
	/*!
	\brief Called when deregistering and object from being updated.

	\par Example:
	\code
	Player::~Player()
	{
		SubmitUpdateDeregistration();
	}
	\endcode
	*/
	void SubmitUpdateDeregistration();

private:
	void SceneRegistration();
	void SceneDeregistration();
	UpdatableManager::StorageListRef pMyDeleteRef;
	RegistrationState regStateCurr;
	UpdateRegistrationCommand* pRegistrationCmd;
	UpdateDeregistrationCommand* pDeregistrationCmd;
	/*!
	\brief To be implemented by derived class and define what to update each frame.

	\par Example:
	\code
	void Bullet::Update()
	{
		pos += Vect(0, 0, speed) * rot;
	
		Matrix world = bulletScale * rot * Matrix(TRANS, pos);
		pGObj_bullet->SetWorld(world);
	
		this->UpdateCollisionData(world, scale);
	}
	\endcode
	*/
	virtual void Update() {};

};