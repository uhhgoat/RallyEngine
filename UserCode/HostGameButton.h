#pragma once
#include "../src/MenuItem.h"
#include "../src/NetworkManager.h"
#include "Status.h"
class HostGameButton : public MenuItem
{
public:
	HostGameButton()
	{
		string->Set("Host Online");
		image = new RallySprite();
		imageFocus = new RallySprite();
		image->SetImage(ImageManager::Get("MenuItem"));
		imageFocus->SetImage(ImageManager::Get("MenuItemFocus"));
	}
	virtual void Action() override
	{
		if (NetworkManager::getState() == NetworkManager::NetworkState::OFFLINE)
		{
			NetworkManager::EstablishHost();
			statusString->SetString("Waiting for client connection...");
		}
	};

	Status* statusString;
};