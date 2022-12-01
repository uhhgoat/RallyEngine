#include "Powerup.h"
#include "BulletFactory.h"
#include "SceneTankBattle.h"
#include "Bullet.h"
Powerup::Powerup(float x, float y, POWERUP_TYPE _type)
{
	Pos.set(x, 0, y);
	Rot.set(IDENTITY);

	Rot = Matrix(ROT_X, -MATH_PI2);

	float terrainOffset = SceneManager::GetCurrentScene()->GetTerrain()->GetHeight(Pos);

	type = _type;
	switch (type)
	{
		case POWERUP_TYPE::HEALTH:
		{
			pGObj_Powerup = new GraphicsObject_WireframeConstantColor(ModelManager::Get("heart"),
				ShaderManager::Get("colorConstantRender"),
				RALLY_COLORS::RED);
			Pos.set(x, 0 + terrainOffset, y);
			scale = 1;
			break;
		}
		case POWERUP_TYPE::SPEED:
		{
			pGObj_Powerup = new GraphicsObject_WireframeConstantColor(ModelManager::Get("arrow"),
				ShaderManager::Get("colorConstantRender"),
				RALLY_COLORS::GREEN);
			Pos.set(x, 10 + terrainOffset, y);
			scale = 15;
			break;
		}
		case POWERUP_TYPE::DAMAGE:
		{
			pGObj_Powerup = new GraphicsObject_WireframeConstantColor(ModelManager::Get("arrow"),
				ShaderManager::Get("colorConstantRender"),
				RALLY_COLORS::PURPLE);
			Pos.set(x, 10 + terrainOffset, y);
			scale = 15;
			break;
		}
		default:
		{
			pGObj_Powerup = new GraphicsObject_WireframeConstantColor(ModelManager::Get("heart"),
				ShaderManager::Get("colorConstantRender"),
				RALLY_COLORS::RED);
			Pos.set(x, 0 + terrainOffset, y);
			scale = 1;
			break;
		}
	}

	Scale.set(SCALE, scale, scale, scale);

	


	SetColliderModel(pGObj_Powerup->getModel(), Collidable::VolumeType::BSPHERE);

	Matrix world = Scale * Rot * Matrix(TRANS, Pos);
	pGObj_Powerup->SetWorld(world);

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();


	SetCollidableGroup<Powerup>();
	SubmitCollisionRegistration();


	color = RALLY_COLORS::WHITE;

	this->UpdateCollisionData(world, scale);
}

Powerup::~Powerup()
{
	delete pGObj_Powerup;
}

void Powerup::Update()
{
	Rot *= Matrix(ROT_Y, 0.1f);
	Matrix world = Scale * Rot * Matrix(TRANS, Pos);
	pGObj_Powerup->SetWorld(world);
}

void Powerup::Draw()
{
	pGObj_Powerup->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	if (BsphereToggle)
	{
		//Visualizer::ShowBSphere(GetBSphere(), color);
	}
	//Visualizer::ShowCollisionVolume(GetCollisionVolume(), RALLY_COLORS::BLUE);
}


void Powerup::Collision(PlayerTank* tank)
{
	AZUL_UNUSED(tank);
	DebugMsg::out("Powerup Collision with Player \n");
	color = RALLY_COLORS::RED;
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
}
void Powerup::Collision(Player2Tank* tank)
{
	AZUL_UNUSED(tank);
	DebugMsg::out("Powerup Collision with Player2 \n");
	color = RALLY_COLORS::RED;
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
}
