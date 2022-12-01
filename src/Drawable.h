#pragma once
#include "DrawableManager.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"
#include "RegistrationState.h"
class Drawable
{
	
	friend class DrawableAttorney;

public:
	Drawable();
	virtual ~Drawable();
	Drawable(const Drawable&) = delete;
	Drawable& operator=(const Drawable&) = delete;

protected:
	/*!
	\brief Called when registering and object to be drawn every frame.

	\par Example:
	\code
	Player::Player()
	{
		SubmitDrawRegistration();
	}
	\endcode
	*/
	void SubmitDrawRegistration();
	/*!
	\brief Called when deregistering and object from being drawn.

	\par Example:
	\code
	Player::~Player()
	{
		SubmitDrawDeregistration();
	}
	\endcode
	*/
	void SubmitDrawDeregistration();

private:
	void SceneRegistration();
	void SceneDeregistration();
	DrawableManager::StorageListRef pMyDeleteRef;
	RegistrationState regStateCurr;
	DrawRegistrationCommand* pRegistrationCmd;
	DrawDeregistrationCommand* pDeregistrationCmd;
	/*!
	\brief To be implemented by derived class and define what to render each frame.

	\par Example:
	\code
	void Bullet::Draw()
	{
		pGObj_bullet->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	}
	\endcode
	*/
	virtual void Draw() {};
	virtual void Draw2D() {};

};
