#pragma once
#include "VisualizeCommand.h"
#include "AzulCore.h"

class VisualizeMinMaxCommand : public VisualizeCommand
{
public:
	void execute();
	VisualizeMinMaxCommand(Vect min, Vect max, const Vect& col);
	Vect MIN;
	Vect MAX;
	const Vect& myCol;

};