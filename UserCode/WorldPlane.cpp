#include "WorldPlane.h"
WorldPlane::WorldPlane()
{
	pGObj_Plane = new GraphicsObject_TextureFlat(ModelManager::Get("plane"),
		ShaderManager::Get("textureFlatRender"),
		TextureManager::Get("grid"));
	pGObj_Axis = new GraphicsObject_ColorNoTexture(ModelManager::Get("plane"),
		ShaderManager::Get("colorNoTextureRender"));


	Matrix world;

	// Axis and Plane
	world = Matrix(IDENTITY);
	pGObj_Axis->SetWorld(world);
	world = Matrix(SCALE, 10, 10, 10);
	pGObj_Plane->SetWorld(world);

	Drawable::SubmitDrawRegistration();
	//Alarmable::SubmitAlarmRegistration(1, AlarmableManager::ALARM_0);
	//Alarmable::SubmitAlarmRegistration(2, AlarmableManager::ALARM_1);
}

WorldPlane::~WorldPlane()
{
	delete pGObj_Plane;
	delete pGObj_Axis;
}

void WorldPlane::Draw()
{
	pGObj_Plane->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	//pGObj_Axis->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

void WorldPlane::Alarm0()
{
	DebugMsg::out("WorldPlane: Ping ONE!\n");
	SubmitAlarmRegistration(2, AlarmableManager::ALARM_0);
}

void WorldPlane::Alarm1()
{
	DebugMsg::out("WorldPlane: Ping TWO!\n");
	SubmitAlarmRegistration(2, AlarmableManager::ALARM_1);
}