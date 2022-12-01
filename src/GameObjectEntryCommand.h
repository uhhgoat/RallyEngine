#pragma once
#include "CommandBase.h"
#include "GameObject.h"
class GameObjectEntryCommand : public CommandBase
{
public:
	GameObject* ptrGO;
	void execute();
	GameObjectEntryCommand(GameObject* go);
private:
};