#pragma once
#include "../src/MenuItem.h"
#include "Status.h"
#include "../src/NetworkManager.h"
#include "SceneTankBattle.h"
class SinglePlayerButton : public MenuItem
{
public:
	SinglePlayerButton()
	{
		string->Set("Solo Game");
		image = new RallySprite();
		imageFocus = new RallySprite();
		image->SetImage(ImageManager::Get("MenuItem"));
		imageFocus->SetImage(ImageManager::Get("MenuItemFocus"));
	}
	virtual void Action() override
	{
		if (NetworkManager::getState() == NetworkManager::NetworkState::OFFLINE)
			SceneManager::SetNextScene(new SceneTankBattle());
		else
			statusString->SetString("Please cancel online connections for single player.");
	};

	Status* statusString;
};