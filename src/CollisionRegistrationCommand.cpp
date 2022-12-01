#include "CollisionRegistrationCommand.h"
#include "CollidableAttorney.h"
CollisionRegistrationCommand::CollisionRegistrationCommand(Collidable* col)
	:ptrCol(col)
{

}
void CollisionRegistrationCommand::execute()
{
	CollidableAttorney::Registration::SceneRegistration(ptrCol);
}