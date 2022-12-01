#pragma once
#include "VisualizeCommand.h"
#include "AzulCore.h"
class CollisionVolumeAABB;

class VisualizeAABBCommand : public VisualizeCommand
{
public:
	void execute();
	VisualizeAABBCommand(const CollisionVolumeAABB& S, const Vect& col);
	const CollisionVolumeAABB& myS;
	const Vect& myCol;

};