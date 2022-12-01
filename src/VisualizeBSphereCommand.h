#pragma once
#include "VisualizeCommand.h"
#include "AzulCore.h"
class CollisionVolumeBSphere;

class VisualizeBSphereCommand : public VisualizeCommand
{
public:
	void execute();
	VisualizeBSphereCommand(const CollisionVolumeBSphere& S, const Vect& col);
	const CollisionVolumeBSphere& myS;
	const Vect& myCol;

};