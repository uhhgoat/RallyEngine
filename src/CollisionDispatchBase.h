#pragma once
#include "AzulCore.h"
class Collidable;
class CollisionDispatchBase
{
public:
	virtual void ProcessCallbacks(Collidable* c1, Collidable* c2) { AZUL_UNUSED(c1); AZUL_UNUSED(c2); };
};