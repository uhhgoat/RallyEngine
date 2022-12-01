#pragma once
#include "../src/MenuItem.h"
#include "Status.h"
#include "SceneTankBattle.h"
class StartOnlineButton : public MenuItem
{
public:
	StartOnlineButton()
	{
		string->Set("Start Online");
		image = new RallySprite();
		imageFocus = new RallySprite();
		image->SetImage(ImageManager::Get("MenuItem"));
		imageFocus->SetImage(ImageManager::Get("MenuItemFocus"));
	}
	virtual void Action() override
	{
		/*HERE HOST NEED TO CHANGE SCENE, SEND START COMMAND TO CLIENT*/
		if (NetworkManager::getState() == NetworkManager::NetworkState::HOST)
		{
			GameStateMessage* nextTankBattle = new GameStateMessage(0);
			NetworkManager::SendData(nextTankBattle);
			SceneManager::SetNextScene(new SceneTankBattle());
		}
	};

	Status* statusString;
};