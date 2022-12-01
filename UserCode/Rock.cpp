#include "Rock.h"
#include "BulletFactory.h"
#include "SceneTankBattle.h"
#include "Bullet.h"
Rock::Rock(float x, float y, int id)
{
	ShipScale.set(SCALE, scale, scale, scale);
	ShipPos.set(x, 0, y);
	ShipPos.set(x, SceneManager::GetCurrentScene()->GetTerrain()->GetHeight(ShipPos), y);
	ShipRot.set(IDENTITY);

	ShipRot = Matrix(ROT_X, -MATH_PI2);

	// Light
	Vect LightColor(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pGObj_Tank = new GraphicsObject_TextureLight(ModelManager::Get("rock"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("rock"),
		LightColor, LightPos);


	SetColliderModel(pGObj_Tank->getModel(), Collidable::VolumeType::OBB);

	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_Tank->SetWorld(world);

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();


	SetCollidableGroup<Rock>();
	SubmitCollisionRegistration();


	color = RALLY_COLORS::WHITE;


	ID = id;
}

Rock::~Rock()
{
	delete pGObj_Tank;
}

void Rock::Update()
{
	if (!transSent && NetworkManager::getState() == NetworkManager::NetworkState::HOST)
	{
		ObjectUpdateMessage* mess = new ObjectUpdateMessage((int)GameManager::OBJ_TYPE::ROCK, ID, world);
		NetworkManager::SendData(mess);
		transSent = true;
	}
	pGObj_Tank->SetWorld(world);

	this->UpdateCollisionData(world, scale);
}

void Rock::Draw()
{
	pGObj_Tank->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	if (BsphereToggle)
	{
		//Visualizer::ShowBSphere(GetBSphere(), color);
	}
	Visualizer::ShowCollisionVolume(GetCollisionVolume(), RALLY_COLORS::BLUE);
}


void Rock::Collision(Bullet* bullet)
{
	AZUL_UNUSED(bullet);
	DebugMsg::out("Rock Collision with Bullet \n");
	color = RALLY_COLORS::RED;
}
