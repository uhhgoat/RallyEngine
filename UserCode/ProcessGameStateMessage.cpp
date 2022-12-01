#include "../src/NetworkManager.h"
#include "../src/SceneManager.h"
#include "../src/EventType.h"
#include "SceneTankBattle.h"

void NetworkManager::ProcessGameStateMessage(GameStateMessage* stateMessage)
{
	switch (stateMessage->GameState)
	{
	case 0:
		SceneManager::SetNextScene(new SceneTankBattle());
		break;
	default:
		break;
	}
	//USER DO WHAT YOU WILL WITH THE MESSAGE
	//SceneTankBattle* scene = (SceneTankBattle*)SceneManager::GetCurrentScene();

}