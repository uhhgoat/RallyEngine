#include "Bullet.h"
#include "BulletFactory.h"
#include "EnemyTank.h"
#include "EnemyFighter.h"
#include "PlayerTank.h"
#include "PlayerTurret.h"
#include "Player2Tank.h"
#include "Player2Turret.h"
#include "Ruins.h"
#include "Rock.h"
#include "../src/Terrain.h"

float Bullet::playerDamage = 10;

Bullet::Bullet()
{
	// Light
	//Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	bulletScale.set(SCALE, scale, scale, scale);
	pGObj_bullet = new GraphicsObject_ColorNoTextureLight(ModelManager::Get("bullet"),
		ShaderManager::Get("colorNoTextureLight"),
		RALLY_COLORS::GREEN, LightPos);

	SetColliderModel(pGObj_bullet->getModel(), Collidable::VolumeType::OBB);
}
Bullet::~Bullet()
{
	delete pGObj_bullet;
}
void Bullet::Update()
{
	pos += Vect(0, 0, speed) * rot;

	Matrix world = bulletScale * rot * Matrix(TRANS, pos);
	pGObj_bullet->SetWorld(world);

	this->UpdateCollisionData(world, scale);
	SceneManager::GetCurrentScene()->GetTerrain()->Intersect(this);
}
void Bullet::Draw()
{
	pGObj_bullet->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	//Visualizer::ShowCollisionVolume(GetCollisionVolume(), RALLY_COLORS::BLUE);
}
void Bullet::Alarm0()
{
	SubmitExit();
}
void Bullet::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitAlarmRegistration(lifetime, AlarmableManager::ALARM_0);

	SetCollidableGroup<Bullet>();
	SubmitCollisionRegistration();

}
void Bullet::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
	//SubmitAlarmDeregistration(AlarmableManager::ALARM_0);

	DebugMsg::out("Bullet Removed!\n");
	BulletFactory::BulletReturn(this);

}
void Bullet::Initialize(Matrix r, Vect m)
{
	rot = r;
	pos = m;
	Matrix world = bulletScale * rot * Matrix(TRANS, pos);
	pGObj_bullet->SetWorld(world);
	DebugMsg::out("Bullet Fired!\n");

}

void Bullet::IncreasePlayerDamage(float amt)
{
	playerDamage += amt;
}

void Bullet::Collision(EnemyTank* tank)
{
	AZUL_UNUSED(tank);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	SubmitExit();
	DebugMsg::out("Bullet Collision with EnemyTank \n");
}
void Bullet::Collision(EnemyFighter* tank)
{
	AZUL_UNUSED(tank);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	SubmitExit();
	DebugMsg::out("Bullet Collision with EnemyTank \n");
}
//*
void Bullet::Collision(PlayerTank* tank)
{
	AZUL_UNUSED(tank);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	SubmitExit();
	DebugMsg::out("Bullet Collision with PlayerTank \n");
}
//*/
void Bullet::Collision(TreeTrunk* tree)
{
	AZUL_UNUSED(tree);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	SubmitExit();
	DebugMsg::out("Bullet Collision with TreeTrunk \n");
}

void Bullet::Collision(PlayerTurret* tank)
{
	AZUL_UNUSED(tank);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	SubmitExit();
	DebugMsg::out("Bullet Collision with PlayerTurret \n");
}

void Bullet::Collision(Player2Tank* tank)
{
	AZUL_UNUSED(tank);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	SubmitExit();
	DebugMsg::out("Bullet Collision with Player2Tank \n");
}

void Bullet::Collision(Player2Turret* tank)
{
	AZUL_UNUSED(tank);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	SubmitExit();
	DebugMsg::out("Bullet Collision with Player2Turret \n");
}

void Bullet::Collision(Ruins* tank)
{
	AZUL_UNUSED(tank);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	SubmitExit();
	DebugMsg::out("Bullet Collision with Ruins \n");
}

void Bullet::Collision(Rock* tank)
{
	AZUL_UNUSED(tank);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	SubmitExit();
	DebugMsg::out("Bullet Collision with Rock \n");
}

void Bullet::CollisionTerrain()
{
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	SubmitExit();
	DebugMsg::out("Bullet Collision with TERRAIN \n");
}
