#include "VisualizeOBBCommand.h"
#include "CollisionVolumeOBB.h"
#include "VisualizerAttorney.h"
VisualizeOBBCommand::VisualizeOBBCommand(const CollisionVolumeOBB& S, const Vect& col)
	:myS(S), myCol(col)
{

}
void VisualizeOBBCommand::execute()
{
	VizualizerAttorney::Show::ShowOBB(myS, myCol);
}