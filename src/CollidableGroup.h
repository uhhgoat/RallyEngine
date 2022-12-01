#pragma once
#include <list>
#include "CollisionVolumeAABB.h"
class Collidable;
class CollidableGroup
{
private:
	CollisionVolumeAABB* groupAABB;

public:
	using StorageList = std::list<Collidable*>;
	StorageList storageList;

	using StorageListRef = StorageList::iterator;

	CollidableGroup();
	~CollidableGroup();
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup& operator=(const CollidableGroup&) = delete;


	void Register(Collidable* col);
	void Deregister(const StorageListRef ref);
	const StorageList& GetColliderCollection();

	void UpdateGroupAABB();
	const CollisionVolumeAABB& GetGroupAABB();
};