#pragma once
#include "AzulCore.h"
#include <list>
#include "EventType.h"
class Inputable;
class SingleKeyEventManager
{
public:
	using InputableCollection = std::list<Inputable*>;
	using StorageListRef = InputableCollection::iterator;

	SingleKeyEventManager() = default;
	~SingleKeyEventManager() = default;
	SingleKeyEventManager(AZUL_KEY k);
	SingleKeyEventManager(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager& operator=(const SingleKeyEventManager&) = delete;

	void Deregister(SingleKeyEventManager::StorageListRef ref, EVENT_TYPE e);
	void Register(Inputable* a, EVENT_TYPE e);
	void ProcessKeyEvents();

	AZUL_KEY getKey();


private:
	AZUL_KEY key;
	bool lastKeyState;
	InputableCollection keyPressedCol;
	InputableCollection keyDownCol;
	InputableCollection keyReleasedCol;

};