#pragma once
#include "CommandBase.h"
#include "GameObject.h"
class GameObjectExitCommand : public CommandBase
{
public:
	GameObject* ptrGO;
	void execute();
	GameObjectExitCommand(GameObject* go);
private:
};