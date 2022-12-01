#pragma once
#include "../src/MenuItem.h"
#include "../src/NetworkManager.h"
#include "Status.h"
class JoinGameButton : public MenuItem
{
public:
	JoinGameButton()
	{
		string->Set("Join Online");
		image = new RallySprite();
		imageFocus = new RallySprite();
		image->SetImage(ImageManager::Get("MenuItem"));
		imageFocus->SetImage(ImageManager::Get("MenuItemFocus"));
	}
	virtual void Action() override
	{
		if (NetworkManager::getState() == NetworkManager::NetworkState::OFFLINE)
		{
			NetworkManager::EstablishClient();
			statusString->SetString("Attempting connection to host...");
		}
	};

	Status* statusString;
};