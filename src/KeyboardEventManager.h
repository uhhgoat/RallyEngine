#pragma once
#include "SingleKeyEventManager.h"
class KeyboardEventManager
{
public:
	static const int EVENTS_NUMBER = 3;
	static const int KEYS_NUMBER = 325;
	using MapKeyManager = std::list<SingleKeyEventManager*>;
	void Register(Inputable* p, AZUL_KEY k, EVENT_TYPE e);
	void Deregister(SingleKeyEventManager::StorageListRef ref, AZUL_KEY k, EVENT_TYPE e);
	void ProcessKeyEvents();
	KeyboardEventManager() = default;
	~KeyboardEventManager();
	KeyboardEventManager(const KeyboardEventManager&) = delete;
	KeyboardEventManager& operator=(const KeyboardEventManager&) = delete;

private:
	MapKeyManager mapSKMgrs;

};