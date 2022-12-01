#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
{
	
}
Scene::~Scene()
{
	
}

void Scene::Update()
{
	RegistrationBrkr.ExecuteCommands();

	AlarmMgr.ProcessAlarms();

	UpdateMgr.ProcessElements();

	InputMgr.ProcessKeyEvents();

	CollMgr.ProcessCollisions();

	CamMgr.UpdateCamera();
}

void Scene::Draw()
{
	//terrain manager draw terrain
	TerMgr.DrawTerrain();

	DrawMgr.ProcessElements();
}

void Scene::SetTerrain(std::string key)
{
	TerMgr.SetCurrentTerrain(TerrainObjectManager::Get(key));
}

void Scene::Register(Updatable* up)
{
	UpdateMgr.Register(up);
}
void Scene::Deregister(UpdatableManager::StorageListRef ref)
{
	UpdateMgr.Deregister(ref);
}
void Scene::Register(Drawable* dr)
{
	DrawMgr.Register(dr);
}
void Scene::Deregister(DrawableManager::StorageListRef ref)
{
	DrawMgr.Deregister(ref);
}
void Scene::Register(float t, AlarmableManager::AlarmEvent alm)
{
	AlarmMgr.Register(t, alm);
}
void Scene::Deregister(AlarmableManager::StorageListRef ref)
{
	AlarmMgr.Deregister(ref);
}
void Scene::Register(Inputable* in, AZUL_KEY k, EVENT_TYPE e)
{
	InputMgr.Register(in, k, e);
}
void Scene::Deregister(SingleKeyEventManager::StorageListRef ref, AZUL_KEY k, EVENT_TYPE e)
{
	InputMgr.Deregister(ref, k, e);
}


CameraManager* Scene::GetCameraManager()
{
	return &CamMgr;
}

Terrain* Scene::GetTerrain()
{
	return TerMgr.GetCurrentTerrain();
}

CollisionManager* Scene::GetCollisionMgr()
{
	return &CollMgr;
}


void Scene::SubmitCommand(CommandBase* cmd)
{
	RegistrationBrkr.AddCommand(cmd);
}
