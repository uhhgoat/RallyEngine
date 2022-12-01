#include "Collidable.h"
void Collidable::SceneRegistration()
{
	assert(regStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneManager::GetCurrentScene()->GetCollisionMgr()->GetColGroup(myID)->Register(this);
	regStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}
void Collidable::SceneDeregistration()
{
	assert(regStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneManager::GetCurrentScene()->GetCollisionMgr()->GetColGroup(myID)->Deregister(pMyDeleteRef);
	regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}
void Collidable::SubmitCollisionRegistration()
{
	assert(regStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(pRegistrationCmd);
	regStateCurr = RegistrationState::PENDING_REGISTRATION;
}
void Collidable::SubmitCollisionDeregistration()
{
	assert(regStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(pDeregistrationCmd);
	regStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Collidable::Collision(Collidable* col)
{
	AZUL_UNUSED(col);
	DebugMsg::out("Collision \n");
}

void Collidable::CollisionTerrain()
{
	DebugMsg::out("Collision with Terrain \n");
}

Collidable::Collidable()
{
	regStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	pRegistrationCmd = new CollisionRegistrationCommand(this);
	pDeregistrationCmd = new CollisionDeregistrationCommand(this);
	colVolume = nullptr;
	defaultBSphere = new CollisionVolumeBSphere();
}
Collidable::~Collidable()
{
	if(colVolume != nullptr)
		delete colVolume;
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
	delete defaultBSphere;
}

const CollisionVolume& Collidable::GetCollisionVolume()
{
	return *colVolume;
}
const CollisionVolumeBSphere& Collidable::GetDefaultBSphere()
{
	return *defaultBSphere;
}
void Collidable::SetColliderModel(Model* mod, VolumeType v)
{
	pColModel = mod;
	switch (v)
	{
		case BSPHERE:
			colVolume = new CollisionVolumeBSphere();
			break;
		case AABB:
			colVolume = new CollisionVolumeAABB();
			break;
		case OBB:
			colVolume = new CollisionVolumeOBB();
			break;
		default:
			break;
	}
}
void Collidable::UpdateCollisionData(Matrix& mat, float scale)
{
	colVolume->ComputeData(pColModel, mat, scale);
	defaultBSphere->ComputeData(pColModel, mat, scale);
}