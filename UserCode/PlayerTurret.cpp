#include "PlayerTurret.h"
#include "BulletFactory.h"
#include "SceneTankBattle.h"
#include "PlayerTank.h"

//TEMPORARY
#include "SceneFrigate.h"
#include "../src/RallyMathTools.h"


PlayerTurret::PlayerTurret()
{
	ShipScale.set(SCALE, scale, scale, scale);
	TurretPos.set(0, 15, 0);
	TurretRot.set(IDENTITY);



	// Light
	//Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	//Vect LightPos(50, 50, 50, 50);
	//*/
	Vect LightPos(x, 50, 0, 0.5f);
	Vect color(0.1f, 0.5f, 0.1f, 0.5f);

	pGObj_Turret = new GraphicsObject_ColorNoTextureLight(ModelManager::Get("t99turret"),
		ShaderManager::Get("colorNoTextureLight"),
		color, LightPos);


	SetColliderModel(pGObj_Turret->getModel(), Collidable::VolumeType::OBB);

	Matrix world = ShipScale * TurretRot * Matrix(TRANS, TurretPos);
	pGObj_Turret->SetWorld(world);

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_Q, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_E, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_RELEASE);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_F, EVENT_TYPE::KEY_PRESS);

	//FOR SCENE CHANGE TESTING
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_0, EVENT_TYPE::KEY_PRESS);

	//SceneManager::GetCurrentScene()->GetCameraManager()->SetFollow();
	//SceneManager::GetCurrentScene()->GetCameraManager()->SetGodCam();

	//SetColliderModel(pGObj_Tank->getModel());

	SetCollidableGroup<PlayerTurret>();
	SubmitCollisionRegistration();

}

PlayerTurret::~PlayerTurret()
{
	delete pGObj_Turret;
}

void PlayerTurret::Update()
{

	//ShipPos = Vect(ShipPos.X(), currentScene->GetTerrain()->GetHeight(ShipPos), ShipPos.Z());
	TurretPos = Vect(player->GetPos().X(), player->GetPos().Y() + 15, player->GetPos().Z());


	Vect TerrainNormal = currentScene->GetTerrain()->GetNormal(player->GetPos());
	Matrix toNormal = RallyMathTools::GetRotationTo(TerrainNormal);
	adjustedTurretRot = TurretRot * toNormal;
	// Spaceship adjust matrix
	Matrix world = ShipScale * adjustedTurretRot * Matrix(TRANS, TurretPos);
	pGObj_Turret->SetWorld(world);


	this->UpdateCollisionData(world, scale);

}

void PlayerTurret::Draw()
{
	pGObj_Turret->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	if (BsphereToggle)
	{
		Visualizer::ShowCollisionVolume(GetCollisionVolume(), RALLY_COLORS::AQUA);
		Visualizer::ShowCollisionVolume(GetDefaultBSphere(), RALLY_COLORS::ORANGE);
	}

	//currentScene->IdentifyTerrainCells(ShipPos, GetDefaultBSphere().GetRadius());
}


/*
Vect PlayerTurret::GetPos()
{
	return TurretPos;
}
//*/

void PlayerTurret::PlayerKilled()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
}

void PlayerTurret::Collision(Bullet* bullet)
{
	AZUL_UNUSED(bullet);
	DebugMsg::out("PlayerTurret Collision with Bullet \n");
	player->TakeDamage();
}