#pragma once
#include "../src/Scene.h"
#include "Frigate.h"
#include "WorldPlane.h"
class SceneFrigate : public Scene
{
public:
	Frigate* frigate;
	WorldPlane* worldPlane;

	void Initialize();
	void Update();
	void Draw();
	void SceneEnd();

private:


};