#include "Ruins.h"
#include "BulletFactory.h"
#include "SceneTankBattle.h"
#include "Bullet.h"
Ruins::Ruins(float x, float y, int id)
{
	ShipScale.set(SCALE, scale, scale, scale);
	ShipPos.set(x, 0, y);
	ShipPos.set(x, SceneManager::GetCurrentScene()->GetTerrain()->GetHeight(ShipPos) + 25, y);
	ShipRot.set(IDENTITY);

	ShipRot = Matrix(ROT_X, -MATH_PI2) * Matrix(ROT_Y, float(rand() % 6));

	// Light
	Vect LightColor(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pGObj_Tank = new GraphicsObject_TextureLight(ModelManager::Get("ruins"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("ruins"),
		LightColor, LightPos);


	SetColliderModel(pGObj_Tank->getModel(), Collidable::VolumeType::OBB);

	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_Tank->SetWorld(world);

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();


	SetCollidableGroup<Ruins>();
	SubmitCollisionRegistration();


	color = RALLY_COLORS::WHITE;


	ID = id;
}

Ruins::~Ruins()
{
	delete pGObj_Tank;
}

void Ruins::Update()
{
	if (!transSent && NetworkManager::getState() == NetworkManager::NetworkState::HOST)
	{
		ObjectUpdateMessage* mess = new ObjectUpdateMessage((int)GameManager::OBJ_TYPE::RUINS, ID, world);
		NetworkManager::SendData(mess);
		transSent = true;
	}
	pGObj_Tank->SetWorld(world);

	this->UpdateCollisionData(world, scale);
}

void Ruins::Draw()
{
	pGObj_Tank->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	if (BsphereToggle)
	{
		//Visualizer::ShowBSphere(GetBSphere(), color);
	}
	Visualizer::ShowCollisionVolume(GetCollisionVolume(), RALLY_COLORS::BLUE);
}


void Ruins::Collision(Bullet* bullet)
{
	AZUL_UNUSED(bullet);
	DebugMsg::out("Ruins Collision with Bullet \n");
	color = RALLY_COLORS::RED;
}
