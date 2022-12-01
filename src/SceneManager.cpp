#include "SceneManager.h"
#include "SceneNull.h"
#include "VisualizerAttorney.h"

SceneManager* SceneManager::ptrInstance = nullptr;

SceneManager::SceneManager()
{
	ptrCurrentScene = new SceneNull();
	sceneChangeCmd = new SceneChangeNullCommand(ptrCurrentScene);
}

void SceneManager::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

SceneManager::~SceneManager()
{
	delete sceneChangeCmd;
	delete ptrCurrentScene;
}

void SceneManager::privInitStartScene()
{
	ptrCurrentScene->Initialize();
}
void SceneManager::privSetNextScene(Scene* newScene)
{
	ptrCurrentScene->SceneEnd();
	VizualizerAttorney::SceneChange::Clear();
	delete ptrCurrentScene;
	delete sceneChangeCmd;
	ptrCurrentScene = newScene;
	ptrCurrentScene->Initialize();
	sceneChangeCmd = new SceneChangeNullCommand(ptrCurrentScene);
}
void SceneManager::privUpdate()
{
	ptrCurrentScene->Update();

	//end of frame create new scene
	sceneChangeCmd->execute();
}
void SceneManager::privDraw()
{
	ptrCurrentScene->Draw();
}
Scene* SceneManager::privGetCurrentScene()
{
	return ptrCurrentScene;
}