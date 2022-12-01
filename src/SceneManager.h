#pragma once
#include <map>
#include <string>
#include "Scene.h"
#include "SceneChangeCommand.h"
#include "SceneChangeNullCommand.h"

class SceneManager
{
private:
	friend class Rally;
	friend class SceneChangeCommand;

	static SceneManager* ptrInstance;

	SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	~SceneManager();


	static SceneManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SceneManager;
		return *ptrInstance;
	};

	Scene* ptrCurrentScene;

	void privInitStartScene();
	//void privSetStartScene(Scene* newScene);
	void privUpdate();
	void privDraw();
	Scene* privGetCurrentScene();
	void privSetNextScene(Scene* sc);
	SceneChangeCommandBase* sceneChangeCmd;

	static void InitStartScene() { Instance().privInitStartScene(); };
	static void Update() { Instance().privUpdate(); };
	static void Draw() { Instance().privDraw(); };
	static void Delete();

public:
	static Scene* GetCurrentScene() { return Instance().privGetCurrentScene(); };
	static void SetNextScene(Scene* sc) {
		delete Instance().sceneChangeCmd;
		Instance().sceneChangeCmd = new SceneChangeCommand(sc);
	};
};
