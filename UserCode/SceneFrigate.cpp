#include "SceneFrigate.h"
#include "BulletFactory.h"
void SceneFrigate::Initialize()
{
	//---------------------------------------------------------------------------------------------------------
	// Graphics Objects
	//---------------------------------------------------------------------------------------------------------

	frigate = new Frigate();
	worldPlane = new WorldPlane();
}

void SceneFrigate::Update()
{
	frigate->Update();
}

void SceneFrigate::Draw()
{
	// draw all objects

	frigate->Draw();
	worldPlane->Draw();
}

void SceneFrigate::SceneEnd()
{

	delete frigate;
	delete worldPlane;
	BulletFactory::Terminate();
}