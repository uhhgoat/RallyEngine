#include "Frigate.h"
#include "BulletFactory.h"

//TEMPORARY
#include "SceneFrigate.h"

Frigate::Frigate()
{
	ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	ShipPos.set(0, 20, 0);
	ShipRot.set(IDENTITY);



	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::Get("space_frigate_mod"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("space_frigate_tex"),
		LightColor, LightPos);

	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	pGObj_SpaceshipBSphere = new GraphicsObject_WireframeConstantColor(ModelManager::GetPremadeModel(Model::PreMadeModels::UnitSphere),
		ShaderManager::Get("colorConstantRender"),
		Blue);



	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, EVENT_TYPE::KEY_DOWN);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_RELEASE);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_F, EVENT_TYPE::KEY_PRESS);

	//FOR SCENE CHANGE TESTING
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_0, EVENT_TYPE::KEY_PRESS);

	//Alarmable::SubmitAlarmRegistration(5, AlarmableManager::ALARM_0);
}

Frigate::~Frigate()
{
	delete pGObj_SpaceFrigateLight;
	delete pGObj_SpaceshipBSphere;
}

void Frigate::Update()
{
	// Spaceship adjust matrix
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);



	// Adjusting the spaceship's bounding sphere
	Vect vBSSize = pGObj_SpaceFrigateLight->getModel()->getRadius() * Vect(1, 1, 1);
	Vect vBSPos = pGObj_SpaceFrigateLight->getModel()->getCenter();

	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix worldBS = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos) * world;

	pGObj_SpaceshipBSphere->SetWorld(worldBS);

	//Camera Follow

	SceneManager::GetCurrentScene()->GetCameraManager()->SetOrientAndPos(Vect(0, 1, 0), ShipPos, (ShipPos + Vect(0, 20, -75) * ShipRot));
}

void Frigate::Draw()
{
	pGObj_SpaceFrigateLight->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	if (BsphereToggle)
	{
		pGObj_SpaceshipBSphere->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	}
}
//*
void Frigate::Alarm0()
{
	//SubmitUpdateDeregistration();
	//SubmitDrawDeregistration();
	BulletFactory::CreateBullet(ShipRot, ShipPos);
}
//*/

void Frigate::KeyDown(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_W:
		ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
		break;
	case AZUL_KEY::KEY_A:
		ShipRot *= Matrix(ROT_Y, ShipRotAng);
		break;
	case AZUL_KEY::KEY_S:
		ShipPos += Vect(0, 0, 1) * ShipRot * -ShipTransSpeed;
		break;
	case AZUL_KEY::KEY_D:
		ShipRot *= Matrix(ROT_Y, -ShipRotAng);
		break;
	default:
		DebugMsg::out("ERROR: Key %i unprocessed\n", k);
	}
}
void Frigate::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_F:
		BulletFactory::CreateBullet(ShipRot, ShipPos);
		break;
	case AZUL_KEY::KEY_SPACE:
		BsphereToggle = true;
		break;
	case AZUL_KEY::KEY_0:
		SceneManager::SetNextScene(new SceneFrigate());
		break;
	default:
		DebugMsg::out("ERROR: Key %i unprocessed\n", k);
	}
}
void Frigate::KeyReleased(AZUL_KEY k)
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