#pragma once
#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
class CollisionTestPairCommand : public CollisionTestCommandBase
{
private:
	CollisionDispatchBase* pDispatch;
	CollidableGroup* pG1;
	CollidableGroup* pG2;

public:
	CollisionTestPairCommand() = default;
	CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd);
	CollisionTestPairCommand(const CollisionTestPairCommand&) = default;
	virtual ~CollisionTestPairCommand();
	void execute();
};