#pragma once
#include "CommandBase.h"
class CollisionTestCommandBase : public CommandBase
{
public:
	virtual void execute() {};
	virtual ~CollisionTestCommandBase(){};
};