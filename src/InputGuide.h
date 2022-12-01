/*! \page inputdemo Adding Keyboard Input

\section inputsetup Inputs
Inputs are a component of GameObject. To give an object access to keyboard input, simply derive from GameObject. \n
A given object may have many different key events associated with it at a time. \n
To utilize these key events, you have to define the three methods associated with the three event types. \n
The available event types are: \n
\code
enum EVENT_TYPE
{
	KEY_PRESS,
	KEY_DOWN,
	KEY_RELEASE
};
\endcode

The methods to define are: \n

\code
virtual void KeyPressed(AZUL_KEY k);
virtual void KeyDown(AZUL_KEY k);
virtual void KeyReleased(AZUL_KEY k);
\endcode

\n
Next, make sure to define what you would like each key to do in each event method.\n
The simplest way to do this is with a switch statement
\n
\code
void Player::KeyDown(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_W:
		ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
		break;
	case AZUL_KEY::KEY_A:
		ShipRot *= Matrix(ROT_Y, ShipRotAng);
		break;
	case AZUL_KEY::KEY_S:
		ShipPos += Vect(0, 0, 1) * ShipRot * -ShipTransSpeed;
		break;
	case AZUL_KEY::KEY_D:
		ShipRot *= Matrix(ROT_Y, -ShipRotAng);
		break;
	default:
		DebugMsg::out("ERROR: Key %i unprocessed\n", k);
	}
}
\endcode
\n
\section inputreg Registration/Deregistration
In order to have the engine recognize the input keys, they need to be registered. \n
Each key must be registered once for each event type you want it to trigger on.
\n
\code
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, EVENT_TYPE::KEY_DOWN);

	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, EVENT_TYPE::KEY_RELEASE);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, EVENT_TYPE::KEY_RELEASE);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, EVENT_TYPE::KEY_RELEASE);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, EVENT_TYPE::KEY_RELEASE);
\endcode
\n
Once you wish for input to no longer trigger for an object, simply deregister the key/event pair the same way.
\n
\code
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_W, EVENT_TYPE::KEY_DOWN);
\endcode

\n
\n
\n

*/