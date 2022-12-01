#include "SingleKeyEventManager.h"
#include "InputableAttorney.h"
SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY k)
{
	key = k;
	lastKeyState = false;
}

void SingleKeyEventManager::Deregister(SingleKeyEventManager::StorageListRef ref, EVENT_TYPE e)
{
	if (e == EVENT_TYPE::KEY_PRESS)
	{
		keyPressedCol.erase(ref);
	}
	if (e == EVENT_TYPE::KEY_DOWN)
	{
		keyDownCol.erase(ref);
	}
	if (e == EVENT_TYPE::KEY_RELEASE)
	{
		keyReleasedCol.erase(ref);
	}
}
void SingleKeyEventManager::Register(Inputable* a, EVENT_TYPE e)
{
	if (e == EVENT_TYPE::KEY_PRESS)
	{
		//CHECK FOR EXISTING
		SingleKeyEventManager::StorageListRef ref = keyPressedCol.insert(keyPressedCol.end(), a);
		InputableAttorney::GameLoop::setStorageRef(a, e, key, ref);
	}
	if (e == EVENT_TYPE::KEY_DOWN)
	{
		SingleKeyEventManager::StorageListRef ref = keyDownCol.insert(keyDownCol.end(), a);
		InputableAttorney::GameLoop::setStorageRef(a, e, key, ref);
	}
	if (e == EVENT_TYPE::KEY_RELEASE)
	{
		SingleKeyEventManager::StorageListRef ref = keyReleasedCol.insert(keyReleasedCol.end(), a);
		InputableAttorney::GameLoop::setStorageRef(a, e, key, ref);
	}
}
void SingleKeyEventManager::ProcessKeyEvents()
{
	//check for KEY down and KEY release through azul then
	//call keypressed and keyreleased on the inputables in the correct lists

	InputableCollection::iterator it;
	
	//if key is down and was up last frame
	if (Keyboard::GetKeyState(key) && !lastKeyState)
	{
		lastKeyState = true;
		for (it = keyPressedCol.begin(); it != keyPressedCol.end(); it++)
		{
			(*it)->KeyPressed(key);
		}
	}
	//if key is down
	if (Keyboard::GetKeyState(key))
	{
		//lastKeyState = true;
		for (it = keyDownCol.begin(); it != keyDownCol.end(); it++)
		{
			(*it)->KeyDown(key);
		}
	}
	//if key is up and was down last frame
	if (!Keyboard::GetKeyState(key) && lastKeyState)
	{
		lastKeyState = false;
		for (it = keyReleasedCol.begin(); it != keyReleasedCol.end(); it++)
		{
			(*it)->KeyReleased(key);
		}
	}
}

AZUL_KEY SingleKeyEventManager::getKey()
{
	return key;
}