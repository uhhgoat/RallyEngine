#include "../src/NetworkManager.h"
#include "../src/SceneManager.h"
#include "../src/EventType.h"
#include "SceneTankBattle.h"

void NetworkManager::ProcessInputMessage(PlayerInputMessage* inputMessage)
{
	//USER DO WHAT YOU WILL WITH THE MESSAGE
	SceneTankBattle* scene = (SceneTankBattle*)SceneManager::GetCurrentScene();
	//*
	if (inputMessage->eventType == EVENT_TYPE::KEY_DOWN)
	{
		switch (inputMessage->key)
		{
		case AZUL_KEY::KEY_W:
			scene->player2->MoveVert(1);
			break;
		case AZUL_KEY::KEY_S:
			scene->player2->MoveVert(-1);
			break;
		case AZUL_KEY::KEY_A:
			scene->player2->Steer(1);
			break;
		case AZUL_KEY::KEY_D:
			scene->player2->Steer(-1);
			break;
		case AZUL_KEY::KEY_Q:
			scene->player2->Aim(1);
			break;
		case AZUL_KEY::KEY_E:
			scene->player2->Aim(-1);
			break;
		default:
			break;
		}
	}
	//*/

	if (inputMessage->eventType == EVENT_TYPE::KEY_PRESS)
	{
		switch (inputMessage->key)
		{
		case AZUL_KEY::KEY_F:
			scene->player2->Fire();
			break;
		default:
			break;
		}
	}
}