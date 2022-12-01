#include "../src/Rally.h"
#include "SceneFrigate.h"
#include "GameManager.h"
void Rally::GameEnd()
{
	SceneManager::GetCurrentScene()->SceneEnd();
	GameManager::Delete();
}