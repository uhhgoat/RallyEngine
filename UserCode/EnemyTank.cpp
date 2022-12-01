#include "EnemyTank.h"
#include "BulletFactory.h"
#include "SceneTankBattle.h"
#include "Bullet.h"
#include "TreeTrunk.h"
#include "../src/RallyMathTools.h"
EnemyTank::EnemyTank(float x, float y, int id)
{
	ShipScale.set(SCALE, scale, scale, scale);
	ShipPos.set(x, 10, y);
	ShipRot.set(IDENTITY);

	ID = id;
	state = STATE::PURSUE;


	// Light
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightColor(1.75f, 0.50f, 0.50f, 1.0f);

	pGObj_Tank = new GraphicsObject_TextureLight(ModelManager::Get("tank1"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("tank1"),
		LightColor, LightPos);


	SetColliderModel(pGObj_Tank->getModel(), Collidable::VolumeType::BSPHERE);

	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_Tank->SetWorld(world);

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	//Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_PRESS);
	//Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_RELEASE);


	target = ((SceneTankBattle*)SceneManager::GetCurrentScene())->player;
	target2 = ((SceneTankBattle*)SceneManager::GetCurrentScene())->player2;

	SetCollidableGroup<EnemyTank>();
	SubmitCollisionRegistration();

	fireRate = 3;
	hitpoints = 50;

	speed = ShipTransSpeed;

	Alarmable::SubmitAlarmRegistration(float(fireRate), AlarmableManager::ALARM_0);
	color = RALLY_COLORS::WHITE;
}

EnemyTank::~EnemyTank()
{
	delete pGObj_Tank;
	
}

void EnemyTank::Update()
{
	if (NetworkManager::getState() == NetworkManager::NetworkState::HOST || NetworkManager::getState() == NetworkManager::NetworkState::OFFLINE)
	{
		//movement (move forward always, will add collision for stopping)
		ShipPos += Vect(0, 0, 1) * ShipRot * speed * (float)state;

		PlaneNormal = Vect(1, 0, 0) * ShipRot;

		float dist1 = (ShipPos - target->GetPos()).magSqr();
		float dist2 = -1;
		if(target2 != nullptr)
			dist2 = (ShipPos - target2->GetPos()).magSqr();

		float d;
		//calculate d, the distance from the tank plane to the target location
		if(dist1 < dist2 || dist2 < 0)
			d = (target->GetPos() - ShipPos).dot(PlaneNormal);
		else
			d = (target2->GetPos() - ShipPos).dot(PlaneNormal);
		

		float distance = (target->GetPos() - ShipPos).magSqr();

		if (distance < range*range)
			inRange = true;
		else
			inRange = false;
		//turning (if facing target, DIR to 0, if target is left, DIR to +1, if target is right, DIR to -1)
		Matrix rotMatrix;
		if (d < -planeDist)
		{
			ShipRotDir = -1.0f;
			rotMatrix = Matrix(ROT_Y, ShipRotAng * ShipRotDir);
			lineOfSight = false;
		}
		else if (d > planeDist)
		{
			ShipRotDir = 1.0f;
			rotMatrix = Matrix(ROT_Y, ShipRotAng * ShipRotDir);
			lineOfSight = false;
		}
		else
		{
			ShipRotDir = 0;
			rotMatrix = Matrix(IDENTITY);
			lineOfSight = true;
		}
		ShipRot *= rotMatrix;



		ShipPos = Vect(ShipPos.X(), currentScene->GetTerrain()->GetHeight(ShipPos) + 10, ShipPos.Z());

		Vect TerrainNormal = currentScene->GetTerrain()->GetNormal(ShipPos);
		Matrix toNormal = RallyMathTools::GetRotationTo(TerrainNormal);
		adjustedRot = ShipRot * toNormal;

		// Spaceship adjust matrix
		world = ShipScale * adjustedRot * Matrix(TRANS, ShipPos);

		// Spaceship adjust matrix
		//Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
		pGObj_Tank->SetWorld(world);

		this->UpdateCollisionData(world, scale);
		ObjectUpdateMessage* upmess = new ObjectUpdateMessage((int)GameManager::OBJ_TYPE::ENEMYTANK, ID, world);
		NetworkManager::SendData(upmess);

	}
	else if (NetworkManager::getState() == NetworkManager::NetworkState::CLIENT)
	{
		// Spaceship adjust matrix
		pGObj_Tank->SetWorld(world);
	}
	
}

void EnemyTank::Draw()
{
	pGObj_Tank->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	if (BsphereToggle)
	{
		//Visualizer::ShowBSphere(GetBSphere(), color);
	}
	Visualizer::ShowCollisionVolume(GetCollisionVolume(), RALLY_COLORS::BLUE);
}
//*
void EnemyTank::Alarm0()
{
	if (lineOfSight)
	{
		//BulletFactory::CreateBullet(adjustedRot, (ShipPos + Vect(0, 17.5f, 50)*adjustedRot));
	}
	SubmitAlarmRegistration(float(rand() % fireRate + fireRate), AlarmableManager::ALARM_0);
}
//*/

void EnemyTank::Alarm1()
{
	state = STATE::PURSUE;
}

void EnemyTank::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		BsphereToggle = true;
		break;
	default:
		DebugMsg::out("ERROR: Key %i unprocessed\n", k);
	}
}
void EnemyTank::KeyReleased(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		BsphereToggle = false;
		break;
	default:
		DebugMsg::out("ERROR: Key %i unprocessed\n", k);
	}
}

void EnemyTank::Collision(Bullet* bullet)
{
	AZUL_UNUSED(bullet);
	DebugMsg::out("EnemyTank Collision with Bullet \n");
	TakeDamage(Bullet::playerDamage);
	color = RALLY_COLORS::RED;
}

void EnemyTank::Collision(PlayerTank* tank)
{
	if (!AlarmActive(AlarmableManager::ALARM_1))
	{
		state = STATE::OBSTACLE;
		SubmitAlarmRegistration(3, AlarmableManager::ALARM_1);
	}
	AZUL_UNUSED(tank);
}

void EnemyTank::Collision(TreeTrunk* tree)
{
	if (!AlarmActive(AlarmableManager::ALARM_1))
	{
		state = STATE::OBSTACLE;
		SubmitAlarmRegistration(3, AlarmableManager::ALARM_1);
	}
	AZUL_UNUSED(tree);
}

void EnemyTank::Collision(Ruins* ruins)
{
	if (!AlarmActive(AlarmableManager::ALARM_1))
	{
		state = STATE::OBSTACLE;
		SubmitAlarmRegistration(3, AlarmableManager::ALARM_1);
	}
	AZUL_UNUSED(ruins);
}

void EnemyTank::Collision(Rock* rock)
{
	if (!AlarmActive(AlarmableManager::ALARM_1))
	{
		state = STATE::OBSTACLE;
		SubmitAlarmRegistration(3, AlarmableManager::ALARM_1);
	}
	AZUL_UNUSED(rock);
}

void EnemyTank::TakeDamage(float damage)
{
	hitpoints -= damage;
	if (hitpoints <= 0)
	{
		currentScene->remainingTanks -= 1;
		currentScene->UpdateRemainingTanks();
		GameManager::AddScore(100);
		SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
		if(AlarmActive(AlarmableManager::ALARM_1))
			SubmitAlarmDeregistration(AlarmableManager::ALARM_1);
		//Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_PRESS);
		//Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_RELEASE);
		SubmitUpdateDeregistration();
		SubmitDrawDeregistration();
		SubmitCollisionDeregistration();
	}
}