#pragma once
#include "../src/MenuItem.h"
#include "../src/NetworkManager.h"
#include "Status.h"
class CancelOnlineButton : public MenuItem
{
public:
	CancelOnlineButton()
	{
		string->Set("Cancel Online");
		image = new RallySprite();
		imageFocus = new RallySprite();
		image->SetImage(ImageManager::Get("MenuItem"));
		imageFocus->SetImage(ImageManager::Get("MenuItemFocus"));
	}
	virtual void Action() override
	{
		NetworkManager::CancelHost();
		NetworkManager::CancelClient();

		statusString->SetString("Lobby Cancelled...");
	};

	Status* statusString;
};