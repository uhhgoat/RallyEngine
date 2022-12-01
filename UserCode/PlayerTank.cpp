#include "PlayerTank.h"
#include "BulletFactory.h"
#include "Powerup.h"
#include "SceneTankBattle.h"
#include "PlayerTurret.h"
#include "TreeTrunk.h"
#include "Ruins.h"
#include "Rock.h"
//TEMPORARY
#include "SceneFrigate.h"
#include "../src/RallyMathTools.h"

int PlayerTank::score = 0;
int PlayerTank::playerID = 0;

PlayerTank::PlayerTank()
{
	float x;
	if (NetworkManager::getState() == NetworkManager::NetworkState::HOST || NetworkManager::getState() == NetworkManager::NetworkState::OFFLINE)
	{
		playerID = 1;
		x = 0;
	}
	else
	{
		playerID = 2;
		x = 150;
	}
	ShipScale.set(SCALE, scale, scale, scale);
	ShipPos.set(x, 0, 0);
	ShipRot.set(IDENTITY);
	//TurretPos.set(0, 15, 0);
	//TurretRot.set(IDENTITY);

	speed = ShipTransSpeed;

	// Light
	Vect LightPos(x, 50, 0, 0.5f);
	Vect color(0.1f, 0.5f, 0.1f, 0.5f);
	//*
	pGObj_Tank = new GraphicsObject_ColorNoTextureLight(ModelManager::Get("t99body"),
		ShaderManager::Get("colorNoTextureLight"),
		color, LightPos);
	//*/

	// Light
	/*
	Vect LightColor(1.50f, 127, 1.50f, 1.0f);
	Vect LightPos(x, 50, 0, 1.0f);

	pGObj_Tank = new GraphicsObject_TextureLight(ModelManager::Get("t99body"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("tank1"),
		LightColor, LightPos);
	*/
/*
	pGObj_Turret = new GraphicsObject_ColorNoTextureLight(ModelManager::Get("t99turret"),
		ShaderManager::Get("colorNoTextureLight"),
		RALLY_COLORS::GREEN, LightPos);
//*/

	SetColliderModel(pGObj_Tank->getModel(), Collidable::VolumeType::OBB);

	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	//Matrix world2 = ShipScale * TurretRot * Matrix(TRANS, TurretPos);
	pGObj_Tank->SetWorld(world);
	//pGObj_Turret->SetWorld(world2);

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

	SceneManager::GetCurrentScene()->GetCameraManager()->SetFollow();
	//SceneManager::GetCurrentScene()->GetCameraManager()->SetGodCam();

	//SetColliderModel(pGObj_Tank->getModel());

	SetCollidableGroup<PlayerTank>();
	SubmitCollisionRegistration();

	turret = new PlayerTurret();
	turret->player = this;
}

PlayerTank::~PlayerTank()
{
	delete pGObj_Tank;
	//delete pGObj_Turret;
	delete turret;
	for (auto&& child : hearts) {
		delete child;
	}
	for (auto&& child : heartsLost) {
		delete child;
	}
}

void PlayerTank::Update()
{
	PrevPos = ShipPos;

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


	//Camera Follow
	Vect up = Vect(0, 1, 0);
	Vect lookAt = ShipPos + Vect(0, 25, 0);
	Vect camPos = (ShipPos + Vect(0, 35, -100) * turret->adjustedTurretRot);
	SceneManager::GetCurrentScene()->GetCameraManager()->UpdateFollowTarget(up, lookAt, camPos);

	this->UpdateCollisionData(world, scale);

	ScreenLog::Add("Pos: %4.1f, %4.1f", ShipPos[x], ShipPos[z]);

	SceneManager::GetCurrentScene()->GetTerrain()->Intersect(this);
}

void PlayerTank::Draw()
{
	pGObj_Tank->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	//pGObj_Turret->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	if (BsphereToggle)
	{
		Visualizer::ShowCollisionVolume(GetCollisionVolume(), RALLY_COLORS::AQUA);
		Visualizer::ShowCollisionVolume(GetDefaultBSphere(), RALLY_COLORS::ORANGE);
	}

	//currentScene->IdentifyTerrainCells(ShipPos, GetDefaultBSphere().GetRadius());
}

void PlayerTank::Draw2D()
{
	for (SpriteTest* child : hearts) {
		child->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera());
	}
	currentScene->DrawHUD();
}


void PlayerTank::KeyDown(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_W:
	{
		ShipPos += Vect(0, 0, 1) * ShipRot  * speed;
		turret->TurretPos += Vect(0, 0, 1) * ShipRot * speed;
		PlayerInputMessage* input = new PlayerInputMessage(playerID, EVENT_TYPE::KEY_DOWN, AZUL_KEY::KEY_W);
		NetworkManager::SendData(input);
		break;
	}
	case AZUL_KEY::KEY_A:
	{
		ShipRot *= Matrix(ROT_Y, ShipRotAng);
		turret->TurretRot *= Matrix(ROT_Y, ShipRotAng);
		PlayerInputMessage* input = new PlayerInputMessage(playerID, EVENT_TYPE::KEY_DOWN, AZUL_KEY::KEY_A);
		NetworkManager::SendData(input);
		break;
	}
	case AZUL_KEY::KEY_S:
	{
		ShipPos += Vect(0, 0, 1) * ShipRot * -speed;
		turret->TurretPos += Vect(0, 0, 1) * ShipRot * -speed;
		PlayerInputMessage* input = new PlayerInputMessage(playerID, EVENT_TYPE::KEY_DOWN, AZUL_KEY::KEY_S);
		NetworkManager::SendData(input);
		break;
	}
	case AZUL_KEY::KEY_D:
	{
		ShipRot *= Matrix(ROT_Y, -ShipRotAng);
		turret->TurretRot *= Matrix(ROT_Y, -ShipRotAng);
		PlayerInputMessage* input = new PlayerInputMessage(playerID, EVENT_TYPE::KEY_DOWN, AZUL_KEY::KEY_D);
		NetworkManager::SendData(input);
		break;
	}
	case AZUL_KEY::KEY_Q:
	{
		turret->TurretRot *= Matrix(ROT_Y, ShipRotAng);
		PlayerInputMessage* input = new PlayerInputMessage(playerID, EVENT_TYPE::KEY_DOWN, AZUL_KEY::KEY_Q);
		NetworkManager::SendData(input);
		break;
	}
	case AZUL_KEY::KEY_E:
	{
		turret->TurretRot *= Matrix(ROT_Y, -ShipRotAng);
		PlayerInputMessage* input = new PlayerInputMessage(playerID, EVENT_TYPE::KEY_DOWN, AZUL_KEY::KEY_E);
		NetworkManager::SendData(input);
		break;
	}
	default:
		DebugMsg::out("ERROR: Key %i unprocessed\n", k);
	}
}
void PlayerTank::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_F:
	{
		BulletFactory::CreateBullet(turret->adjustedTurretRot, (ShipPos + Vect(0, 19.5f, 60) * turret->adjustedTurretRot));
		PlayerInputMessage* input = new PlayerInputMessage(playerID, EVENT_TYPE::KEY_PRESS, AZUL_KEY::KEY_F);
		NetworkManager::SendData(input);
		break;
	}
	case AZUL_KEY::KEY_SPACE:
	{
		BsphereToggle = true;
		//TakeDamage();
		break;
	}
	case AZUL_KEY::KEY_0:
	{
		//SceneManager::SetNextScene(new SceneFrigate());
		GameStateMessage* nextTankBattle = new GameStateMessage(0);
		NetworkManager::SendData(nextTankBattle);
		SceneManager::SetNextScene(new SceneTankBattle());
		break;
	}
	default:
		DebugMsg::out("ERROR: Key %i unprocessed\n", k);
	}
}
void PlayerTank::KeyReleased(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
	{
		BsphereToggle = false;
		break;
	}
	default:
		DebugMsg::out("ERROR: Key %i unprocessed\n", k);
	}
}

Vect PlayerTank::GetPos()
{
	return ShipPos;
}

void PlayerTank::SetSpeed(float _speed)
{
	speed = _speed;
}

void PlayerTank::ResetSpeed()
{
	speed = ShipTransSpeed;
}

void PlayerTank::TakeDamage()
{
	hitpoints -= 1;
	SpriteTest* heart = hearts.back();
	hearts.back()->Remove();
	heartsLost.push_back(heart);
	hearts.pop_back();
	if (hitpoints <= 0)
	{

		Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_W, EVENT_TYPE::KEY_DOWN);
		Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_A, EVENT_TYPE::KEY_DOWN);
		Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_S, EVENT_TYPE::KEY_DOWN);
		Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_D, EVENT_TYPE::KEY_DOWN);
		Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_Q, EVENT_TYPE::KEY_DOWN);
		Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_E, EVENT_TYPE::KEY_DOWN);
		Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_PRESS);
		Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_RELEASE);
		Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_F, EVENT_TYPE::KEY_PRESS);
		//Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_0, EVENT_TYPE::KEY_PRESS);

		SubmitUpdateDeregistration();
		SubmitDrawDeregistration();
		SubmitCollisionDeregistration();
		GameManager::GetEnemiesSS()->Set("YOU DIED");
		turret->PlayerKilled();
	}
}

void PlayerTank::Heal()
{
	if (hitpoints < 3)
	{
		hitpoints += 1;
		SpriteTest* heart = heartsLost.back();
		heartsLost.back()->Remove();
		hearts.push_back(heart);
		heartsLost.pop_back();
	}
}

void PlayerTank::Collision(Bullet* bullet)
{
	AZUL_UNUSED(bullet);
	DebugMsg::out("PlayerTank Collision with Bullet \n");
	TakeDamage();
}

void PlayerTank::Collision(EnemyTank* tank)
{
	AZUL_UNUSED(tank);
	ShipPos = PrevPos;
}

void PlayerTank::Collision(EnemyFighter* tank)
{
	AZUL_UNUSED(tank);
	ShipPos = PrevPos;
}

void PlayerTank::Collision(TreeTrunk* tree)
{
	AZUL_UNUSED(tree);
	ShipPos = PrevPos;
}

void PlayerTank::Collision(Ruins* ruins)
{
	AZUL_UNUSED(ruins);
	ShipPos = PrevPos;
}

void PlayerTank::Collision(Rock* rock)
{
	AZUL_UNUSED(rock);
	ShipPos = PrevPos;
}

void PlayerTank::Collision(Powerup* power)
{
	switch (power->type)
	{
		case POWERUP_TYPE::DAMAGE:
			Bullet::IncreasePlayerDamage(10);
			break;
		case POWERUP_TYPE::HEALTH:
			Heal();
			break;
		case POWERUP_TYPE::SPEED:
			speed += 0.15f;
			break;
		default:
			break;
	}
	DebugMsg::out("PlayerTank Collision with Powerup \n");
}