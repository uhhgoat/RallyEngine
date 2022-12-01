#pragma once
#include "CommandBase.h"
class Collidable;
class CollisionRegistrationCommand : public CommandBase
{
public:
	Collidable* ptrCol;
	void execute();
	CollisionRegistrationCommand(Collidable* col);
private:
};