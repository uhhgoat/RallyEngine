#pragma once
#include <list>
class Updatable;
class UpdatableManager
{
private:
	using StorageList = std::list<Updatable*>;
	StorageList storageList;

public:
	using StorageListRef = StorageList::iterator;

	UpdatableManager() = default;
	~UpdatableManager();
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator=(const UpdatableManager&) = delete;

	void ProcessElements();

	void Register(Updatable* up);
	void Deregister(UpdatableManager::StorageListRef ref);
};