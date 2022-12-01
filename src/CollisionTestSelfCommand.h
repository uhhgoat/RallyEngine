#pragma once
#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
class CollisionTestSelfCommand : public CollisionTestCommandBase
{
private:
	CollisionDispatchBase* pDispatch;
	CollidableGroup* pG;

public:
	CollisionTestSelfCommand() = default;
	CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* pd);
	CollisionTestSelfCommand(const CollisionTestSelfCommand&) = default;
	virtual ~CollisionTestSelfCommand();
	void execute();
};