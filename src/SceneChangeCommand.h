#pragma once
#include "SceneChangeCommandBase.h"
#include "Scene.h"
class SceneChangeCommand : public SceneChangeCommandBase
{
public:
	SceneChangeCommand(Scene* sc);
	virtual void execute();
	Scene* scene;
};