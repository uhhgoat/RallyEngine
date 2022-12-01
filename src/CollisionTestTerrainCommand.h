#pragma once
#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"
class CollisionTestTerrainCommand : public CollisionTestCommandBase
{
private:
	CollidableGroup* pG;

public:
	CollisionTestTerrainCommand() = default;
	CollisionTestTerrainCommand(CollidableGroup* g);
	CollisionTestTerrainCommand(const CollisionTestTerrainCommand&) = default;
	virtual ~CollisionTestTerrainCommand();
	void execute();
};