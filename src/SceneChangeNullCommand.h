#pragma once
#include "SceneChangeCommandBase.h"
#include "Scene.h"
#include "AzulCore.h"
class SceneChangeNullCommand : public SceneChangeCommandBase
{
public:
	SceneChangeNullCommand(Scene* sc)
	{
		AZUL_UNUSED(sc);
	};
	virtual void execute() {};
};