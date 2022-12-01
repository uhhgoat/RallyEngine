#include "KeyboardEventManager.h"
void KeyboardEventManager::Register(Inputable* p, AZUL_KEY k, EVENT_TYPE e)
{
	//check for existing SKmgr, otherwise create one
	bool foundkey = false;
	for (MapKeyManager::iterator it = mapSKMgrs.begin(); it != mapSKMgrs.end(); it++)
	{
		if ((*it)->getKey() == k)
		{
			(*it)->Register(p, e);
			foundkey = true;
			break;
		}
	}
	if (!foundkey)
	{
		SingleKeyEventManager* skem = new SingleKeyEventManager(k);
		skem->Register(p, e);
		mapSKMgrs.insert(mapSKMgrs.end(), skem);
	}
}
void KeyboardEventManager::Deregister(SingleKeyEventManager::StorageListRef ref, AZUL_KEY k, EVENT_TYPE e)
{
	for (MapKeyManager::iterator it = mapSKMgrs.begin(); it != mapSKMgrs.end(); it++)
	{
		if ((*it)->getKey() == k)
		{
			(*it)->Deregister(ref, e);
			break;
		}
	}
}
void KeyboardEventManager::ProcessKeyEvents()
{
	//run through list and process key events on each mgr
	MapKeyManager::iterator it;
	for (it = mapSKMgrs.begin(); it != mapSKMgrs.end(); it++)
	{
		(*it)->ProcessKeyEvents();
	}
}

KeyboardEventManager::~KeyboardEventManager()
{
	for (auto&& child : mapSKMgrs) {
		delete child;
	}
}