#pragma once
#include "AzulCore.h"
#include "SceneManager.h"
#include "RegistrationState.h"
#include "EventType.h"
#include "SingleKeyEventManager.h"
class InputRegistrationCommand;
class InputDeregistrationCommand;

class Inputable
{
private:
	void SceneRegistration(AZUL_KEY k, EVENT_TYPE e);
	void SceneDeregistration(AZUL_KEY k, EVENT_TYPE e);

	void setStorageRef(EVENT_TYPE e, AZUL_KEY k, SingleKeyEventManager::StorageListRef ref);


	struct RegistrationData
	{
		SingleKeyEventManager::StorageListRef pMyDeleteRef;
		RegistrationState regStateCurr;
		InputRegistrationCommand* pRegistrationCmd;
		InputDeregistrationCommand* pDeregistrationCmd;
	};

	std::map<AZUL_KEY, RegistrationData> pCmdsPress;
	std::map<AZUL_KEY, RegistrationData> pCmdsRelease;
	std::map<AZUL_KEY, RegistrationData> pCmdsDown;

public:
	Inputable();
	virtual ~Inputable();
	Inputable(const Inputable&) = delete;
	Inputable& operator=(const Inputable&) = delete;
	/*!
	\brief Called when registering and object to be have key events.\n
	First Parameter is the key, second is the event type.

	\par Example:
	\code
	Player::Player()
	{
		Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, EVENT_TYPE::KEY_DOWN);
	}
	\endcode
	*/
	void SubmitKeyRegistration(AZUL_KEY k, EVENT_TYPE e);
	/*!
	\brief Called when deregistering and object from having key events.

	\par Example:
	\code
	Player::~Player()
	{
		Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_W, EVENT_TYPE::KEY_DOWN);
	}
	\endcode
	*/
	void SubmitKeyDeregistration(AZUL_KEY k, EVENT_TYPE e);
	/*!
	\brief To be implemented by derived class and define what to happen on each key event.

	\par Example:
	\code
	void Player::KeyDown(AZUL_KEY k)
	{
		switch (k)
		{
		case AZUL_KEY::KEY_W:
			ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
			break;
		default:
			DebugMsg::out("ERROR: Key %i unprocessed\n", k);
		}
	}
	\endcode
	*/
	virtual void KeyPressed(AZUL_KEY k) { AZUL_UNUSED(k); };
	virtual void KeyDown(AZUL_KEY k) { AZUL_UNUSED(k); };
	virtual void KeyReleased(AZUL_KEY k) { AZUL_UNUSED(k); };


	friend class InputableAttorney;
};