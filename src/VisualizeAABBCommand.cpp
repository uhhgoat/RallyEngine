#include "VisualizeAABBCommand.h"
#include "CollisionVolumeAABB.h"
#include "VisualizerAttorney.h"
VisualizeAABBCommand::VisualizeAABBCommand(const CollisionVolumeAABB& S, const Vect& col)
	:myS(S), myCol(col)
{

}
void VisualizeAABBCommand::execute()
{
	VizualizerAttorney::Show::ShowAABB(myS, myCol);
}