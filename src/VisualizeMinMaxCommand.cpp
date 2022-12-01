#include "VisualizeMinMaxCommand.h"
#include "CollisionVolumeAABB.h"
#include "VisualizerAttorney.h"
VisualizeMinMaxCommand::VisualizeMinMaxCommand(Vect min, Vect max, const Vect& col)
	:myCol(col)
{
	MIN = min;
	MAX = max;
}
void VisualizeMinMaxCommand::execute()
{
	VizualizerAttorney::Show::ShowAABB(MIN, MAX, myCol);
}