#pragma once
#include "../src/MenuItem.h"
class Title : public MenuItem
{
public:
	Title()
	{
		string->Set("TANK BATTLE");
	};
	virtual void Action() override {};
};