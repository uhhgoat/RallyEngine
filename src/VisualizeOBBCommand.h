#pragma once
#include "VisualizeCommand.h"
#include "AzulCore.h"
class CollisionVolumeOBB;

class VisualizeOBBCommand : public VisualizeCommand
{
public:
	void execute();
	VisualizeOBBCommand(const CollisionVolumeOBB& S, const Vect& col);
	const CollisionVolumeOBB& myS;
	const Vect& myCol;

};