#include "Player2Turret.h"
#include "BulletFactory.h"
#include "SceneTankBattle.h"
#include "Player2Tank.h"

//TEMPORARY
#include "SceneFrigate.h"
#include "../src/RallyMathTools.h"


Player2Turret::Player2Turret()
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

	SetCollidableGroup<Player2Turret>();
	SubmitCollisionRegistration();

}

Player2Turret::~Player2Turret()
{
	delete pGObj_Turret;
}

void Player2Turret::Update()
{

	//ShipPos = Vect(ShipPos.X(), currentScene->GetTerrain()->GetHeight(ShipPos), ShipPos.Z());
	TurretPos = Vect(player2->GetPos().X(), player2->GetPos().Y() + 15, player2->GetPos().Z());

	Vect TerrainNormal = currentScene->GetTerrain()->GetNormal(player2->GetPos());
	Matrix toNormal = RallyMathTools::GetRotationTo(TerrainNormal);
	adjustedTurretRot = TurretRot * toNormal;
	// Spaceship adjust matrix
	Matrix world = ShipScale * adjustedTurretRot * Matrix(TRANS, TurretPos);
	pGObj_Turret->SetWorld(world);


	this->UpdateCollisionData(world, scale);

}

void Player2Turret::Draw()
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
Vect Player2Turret::GetPos()
{
	return TurretPos;
}
//*/

void Player2Turret::Player2Killed()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
}

void Player2Turret::Collision(Bullet* bullet)
{
	AZUL_UNUSED(bullet);
	DebugMsg::out("Player2Turret Collision with Bullet \n");
	player2->TakeDamage();
}