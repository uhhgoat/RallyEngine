#include "Player2Tank.h"
#include "BulletFactory.h"
#include "Player2Turret.h"

#include "SceneTankBattle.h"

//TEMPORARY
#include "SceneFrigate.h"
#include "GameManager.h"
#include "../src/RallyMathTools.h"

int Player2Tank::score = 0;
int Player2Tank::playerID = 0;

Player2Tank::Player2Tank()
{

	if (NetworkManager::getState() == NetworkManager::NetworkState::HOST)
	{
		playerID = 2;
		ShipPos.set(150, 0, 0);
		//TurretPos.set(150, 15, 0);
	}
	else
	{
		playerID = 1;
		ShipPos.set(0, 0, 0);
		//TurretPos.set(0, 15, 0);
	}

	//ShipPos.set(150, 0, 0);
	//TurretPos.set(150, 15, 0);
	ShipScale.set(SCALE, scale, scale, scale);
	ShipRot.set(IDENTITY);
	//TurretRot.set(IDENTITY);



	// Light
	//Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	//Vect LightPos(50, 50, 50, 50);
	Vect LightPos(x, 50, 0, 0.5f);
	Vect color(0.1f, 0.5f, 0.1f, 0.5f);
	//*
	pGObj_Tank = new GraphicsObject_ColorNoTextureLight(ModelManager::Get("t99body"),
		ShaderManager::Get("colorNoTextureLight"),
		color, LightPos);
	//*/

	


	SetColliderModel(pGObj_Tank->getModel(), Collidable::VolumeType::OBB);

	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	//world2 = ShipScale * TurretRot * Matrix(TRANS, TurretPos);
	pGObj_Tank->SetWorld(world);
	//pGObj_Turret->SetWorld(world2);

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();



	//SceneManager::GetCurrentScene()->GetCameraManager()->SetFollow();
	//SceneManager::GetCurrentScene()->GetCameraManager()->SetGodCam();

	//SetColliderModel(pGObj_Tank->getModel());

	SetCollidableGroup<Player2Tank>();
	SubmitCollisionRegistration();

	turret = new Player2Turret();
	turret->player2 = this;

}

Player2Tank::~Player2Tank()
{
	delete pGObj_Tank;
	delete turret;
	//delete pGObj_Turret;
	//for (auto&& child : hearts) {
	//	delete child;
	//}
	//for (auto&& child : heartsLost) {
	//	delete child;
	//}
}

void Player2Tank::Update()
{

	ShipPos = Vect(ShipPos.X(), currentScene->GetTerrain()->GetHeight(ShipPos), ShipPos.Z());
	//turret->TurretPos = Vect(turret->TurretPos.X(), ShipPos.Y() + 15, turret->TurretPos.Z());

	Vect TerrainNormal = currentScene->GetTerrain()->GetNormal(ShipPos);
	Matrix toNormal = RallyMathTools::GetRotationTo(TerrainNormal);
	Matrix newRot = ShipRot * toNormal;
	//adjustedTurretRot = Matrix(ROT_Y, -MATH_PI2) * TurretRot * toNormalX * toNormalZ;
	// Spaceship adjust matrix
	world = ShipScale * newRot * Matrix(TRANS, ShipPos);
	//Matrix world2 = ShipScale * adjustedTurretRot * Matrix(TRANS, TurretPos);
	pGObj_Tank->SetWorld(world);
	//pGObj_Turret->SetWorld(world2);

	/*
	if (NetworkManager::getState() == NetworkManager::NetworkState::HOST)
	{
		ObjectUpdateMessage* upmess = new ObjectUpdateMessage(DataMessage::SEND_TYPE::NETWORKED, (int)GameManager::OBJ_TYPE::PLAYER, playerID, world);
		NetworkManager::SendData(upmess);
	}
	//*/
;

	this->UpdateCollisionData(world, scale);

}

void Player2Tank::Draw()
{
	pGObj_Tank->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	//pGObj_Turret->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	if (BsphereToggle)
	{
		Visualizer::ShowCollisionVolume(GetCollisionVolume(), RALLY_COLORS::AQUA);
		Visualizer::ShowCollisionVolume(GetDefaultBSphere(), RALLY_COLORS::ORANGE);
	}
}

void Player2Tank::Draw2D()
{
	//for (SpriteTest* child : hearts) {
	//	child->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera());
	//}
	//currentScene->DrawHUD();
}

Vect Player2Tank::GetPos()
{
	return ShipPos;
}

void Player2Tank::MoveVert(float dir)
{
	ShipPos += Vect(0, 0, 1) * ShipRot * (ShipTransSpeed * dir);
	turret->TurretPos += Vect(0, 0, 1) * ShipRot * (ShipTransSpeed * dir);
}

void Player2Tank::Steer(float dir)
{
	ShipRot *= Matrix(ROT_Y, ShipRotAng * dir);
	turret->TurretPos *= Matrix(ROT_Y, ShipRotAng * dir);
}

void Player2Tank::Aim(float dir)
{
	turret->TurretRot *= Matrix(ROT_Y, ShipRotAng * dir);
}

void Player2Tank::Fire()
{
	BulletFactory::CreateBullet(turret->TurretRot, (ShipPos + Vect(0, 19.5f, 50) * turret->TurretRot));
}

void Player2Tank::TakeDamage()
{
	hitpoints -= 1;
	//SpriteTest* heart = hearts.back();
	//hearts.back()->Remove();
	//heartsLost.push_back(heart);
	//hearts.pop_back();
	if (hitpoints <= 0)
	{


		SubmitUpdateDeregistration();
		SubmitDrawDeregistration();
		SubmitCollisionDeregistration();
		//currentScene->SStest->Set("YOU DIED");
	}
}

void Player2Tank::Collision(Bullet* bullet)
{
	AZUL_UNUSED(bullet);
	DebugMsg::out("Player2Tank Collision with Bullet \n");
	TakeDamage();
}