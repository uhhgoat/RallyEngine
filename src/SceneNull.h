#pragma once
#include "Scene.h"
class SceneNull : public Scene
{
	virtual void Initialize() {};
	virtual void SceneEnd() {};
};