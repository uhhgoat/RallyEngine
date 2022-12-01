#include "CollisionDeregistrationCommand.h"
#include "CollidableAttorney.h"
CollisionDeregistrationCommand::CollisionDeregistrationCommand(Collidable* col)
	:ptrCol(col)
{

}
void CollisionDeregistrationCommand::execute()
{
	CollidableAttorney::Registration::SceneDeregistration(ptrCol);
}