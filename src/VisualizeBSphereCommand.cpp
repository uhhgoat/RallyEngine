#include "VisualizeBSphereCommand.h"
#include "CollisionVolumeBSphere.h"
#include "VisualizerAttorney.h"
VisualizeBSphereCommand::VisualizeBSphereCommand(const CollisionVolumeBSphere& S, const Vect& col)
	:myS(S), myCol(col)
{

}
void VisualizeBSphereCommand::execute()
{
	VizualizerAttorney::Show::ShowBSphere(myS, myCol);
}