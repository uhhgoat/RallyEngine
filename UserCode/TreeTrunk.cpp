#include "TreeTrunk.h"
#include "BulletFactory.h"
#include "SceneTankBattle.h"
#include "Bullet.h"
TreeTrunk::TreeTrunk(float x, float y, int id)
{
	ShipScale.set(SCALE, scale, scale, scale);
	ShipPos.set(x, 0, y);
	ShipPos.set(x, SceneManager::GetCurrentScene()->GetTerrain()->GetHeight(ShipPos), y);
	ShipRot.set(IDENTITY);

	ShipRot = Matrix(ROT_X, -MATH_PI2);

	// Light
	Vect LightColor(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pGObj_Tank = new GraphicsObject_TextureLight(ModelManager::Get("tree"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("tree"),
		LightColor, LightPos);


	SetColliderModel(pGObj_Tank->getModel(), Collidable::VolumeType::OBB);

	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_Tank->SetWorld(world);

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();


	SetCollidableGroup<TreeTrunk>();
	SubmitCollisionRegistration();


	color = RALLY_COLORS::WHITE;

	
	ID = id;
}

TreeTrunk::~TreeTrunk()
{
	delete pGObj_Tank;
}

void TreeTrunk::Update()
{
	if (!transSent && NetworkManager::getState() == NetworkManager::NetworkState::HOST)
	{
		ObjectUpdateMessage* mess = new ObjectUpdateMessage((int)GameManager::OBJ_TYPE::TREE, ID, world);
		NetworkManager::SendData(mess);
		transSent = true;
	}
	pGObj_Tank->SetWorld(world);

	this->UpdateCollisionData(world, scale);
}

void TreeTrunk::Draw()
{
	pGObj_Tank->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	if (BsphereToggle)
	{
		//Visualizer::ShowBSphere(GetBSphere(), color);
	}
	Visualizer::ShowCollisionVolume(GetCollisionVolume(), RALLY_COLORS::BLUE);
}


void TreeTrunk::Collision(Bullet* bullet)
{
	AZUL_UNUSED(bullet);
	DebugMsg::out("TreeTrunk Collision with Bullet \n");
	color = RALLY_COLORS::RED;
}
