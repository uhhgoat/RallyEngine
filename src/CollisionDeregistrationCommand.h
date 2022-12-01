#pragma once
#include "CommandBase.h"
class Collidable;
class CollisionDeregistrationCommand : public CommandBase
{
public:
	Collidable* ptrCol;
	void execute();
	CollisionDeregistrationCommand(Collidable* col);
private:
};