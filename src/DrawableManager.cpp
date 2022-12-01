#include "DrawableManager.h"
#include "DrawableAttorney.h"
DrawableManager::~DrawableManager()
{

}

void DrawableManager::ProcessElements()
{
	std::list<Drawable*>::iterator it;
	for (it = storageList.begin(); it != storageList.end(); ++it)
	{
		DrawableAttorney::GameLoop::Draw(*it);
	}
	for (it = storageList.begin(); it != storageList.end(); ++it)
	{
		DrawableAttorney::GameLoop::Draw2D(*it);
	}
}
void DrawableManager::Register(Drawable* dr)
{
	DrawableManager::StorageListRef ref = storageList.insert(storageList.end(), dr);
	DrawableAttorney::GameLoop::setStorageRef(dr, ref);
}
void DrawableManager::Deregister(DrawableManager::StorageListRef ref)
{
	storageList.erase(ref);
}