#include "../src/NetworkManager.h"
#include "../src/SceneManager.h"
#include "../src/EventType.h"
#include "SceneTankBattle.h"
#include "GameManager.h"

void NetworkManager::ProcessUpdateMessage(ObjectUpdateMessage* updateMessage)
{
	AZUL_UNUSED(updateMessage);
	//USER DO WHAT YOU WILL WITH THE MESSAGE
	SceneTankBattle* scene = (SceneTankBattle*)SceneManager::GetCurrentScene();

	if (updateMessage->ObjectTypeID == (int)GameManager::OBJ_TYPE::ENEMYTANK)
	{
		GameManager::GetEnemy(updateMessage->ObjectID)->world = updateMessage->Transform;
	}
	else if (updateMessage->ObjectTypeID == (int)GameManager::OBJ_TYPE::ENEMYFIGHTER)
	{
		GameManager::GetFighter(updateMessage->ObjectID)->world = updateMessage->Transform;
	}
	else if (updateMessage->ObjectTypeID == (int)GameManager::OBJ_TYPE::PLAYER)
	{
		if (scene->player->playerID == updateMessage->ObjectID)
		{
			scene->player->world = updateMessage->Transform;
		}
		else if (scene->player2->playerID == updateMessage->ObjectID)
		{
			scene->player2->world = updateMessage->Transform;
		}
	}
	else if (updateMessage->ObjectTypeID == (int)GameManager::OBJ_TYPE::TREE)
	{
		GameManager::GetTree(updateMessage->ObjectID)->world = updateMessage->Transform;
	}
	else if (updateMessage->ObjectTypeID == (int)GameManager::OBJ_TYPE::ROCK)
	{
		GameManager::GetRock(updateMessage->ObjectID)->world = updateMessage->Transform;
	}
	else if (updateMessage->ObjectTypeID == (int)GameManager::OBJ_TYPE::RUINS)
	{
		GameManager::GetRuins(updateMessage->ObjectID)->world = updateMessage->Transform;
	}
	


}