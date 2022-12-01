#include "UpdatableManager.h"
#include "UpdatableAttorney.h"
UpdatableManager::~UpdatableManager()
{

}

void UpdatableManager::ProcessElements()
{
	std::list<Updatable*>::iterator it;
	for (it = storageList.begin(); it != storageList.end(); ++it)
	{
		UpdatableAttorney::GameLoop::Update(*it);
	}
}
void UpdatableManager::Register(Updatable* up)
{
	UpdatableManager::StorageListRef ref = storageList.insert(storageList.end(), up);
	UpdatableAttorney::GameLoop::setStorageRef(up, ref);
}
void UpdatableManager::Deregister(UpdatableManager::StorageListRef ref)
{
	storageList.erase(ref);
}