#pragma once
#include <list>
class Drawable;
class DrawableManager
{
private:
	using StorageList = std::list<Drawable*>;
	StorageList storageList;

public:
	using StorageListRef = StorageList::iterator;

	DrawableManager() = default;
	~DrawableManager();
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator=(const DrawableManager&) = delete;

	void ProcessElements();

	void Register(Drawable* dr);
	void Deregister(DrawableManager::StorageListRef ref);
};