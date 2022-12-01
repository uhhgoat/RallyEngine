#ifndef CollisionManager_H
#define CollisionManager_H
#pragma once
#include "CollidableGroup.h"
#include "CollisionTestCommandBase.h"
#include "CollisionDispatch.h"
#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"
#include "CollisionTestTerrainCommand.h"
class CollisionManager
{
public:
	friend class SceneManager;
	using TypeID = int;
	static const TypeID ID_UNDEFINED = -1;

private:
	static const int maxCollidables = 16;
	using CollidableGroupCollection = CollidableGroup*;
	CollidableGroupCollection ColGroupCollection[maxCollidables];

	using CollisionTestCommands = std::list<CollisionTestCommandBase*>;
	CollisionTestCommands colTestCommands;




	TypeID TypeIDNextNumber;

	void SetGroupForTypeID(TypeID ind);

public:
	CollisionManager() = default;
	~CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;

	template <typename C>
	TypeID GetTypeID()
	{

		static TypeID myTypeID = TypeIDNextNumber++;

		SetGroupForTypeID(myTypeID);

		return myTypeID;

	}

	template< typename C1, typename C2>
	void SetCollisionPair()
	{
		CollidableGroup* pg1 = ColGroupCollection[GetTypeID<C1>()];
		CollidableGroup* pg2 = ColGroupCollection[GetTypeID<C2>()];

		CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();

		colTestCommands.push_back(new CollisionTestPairCommand(pg1, pg2, pDispatch));
	}

	template< typename C>
	void SetCollisionSelf()
	{
		CollidableGroup* pg = ColGroupCollection[GetTypeID<C>()];

		CollisionDispatch<C, C>* pDispatch = new CollisionDispatch<C, C>();

		colTestCommands.push_back(new CollisionTestSelfCommand(pg, pDispatch));
	}

	template<typename C>
	void SetCollisionTerrain()
	{
		CollidableGroup* pg = ColGroupCollection[GetTypeID<C>()];
		colTestCommands.push_back(new CollisionTestTerrainCommand(pg));
	}

	CollidableGroup* GetColGroup(TypeID id);

	void ProcessCollisions();
};
#endif