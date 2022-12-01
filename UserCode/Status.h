#pragma once
#include "../src/MenuItem.h"
class Status : public MenuItem
{
public:
	Status()
	{
		string->Set("...");
	};
	virtual void Action() override {};
};