#pragma once
#include "CommandBase.h"
#include <list>
class SceneRegistrationBroker
{
public:
	void AddCommand(CommandBase* c);
	void ExecuteCommands();
private:
	using CommandList = std::list<CommandBase*>;
	CommandList listCommands;
};