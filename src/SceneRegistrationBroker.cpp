#include "SceneRegistrationBroker.h"
void SceneRegistrationBroker::AddCommand(CommandBase* c)
{
	listCommands.push_back(c);
}
void SceneRegistrationBroker::ExecuteCommands()
{
	for (CommandList::const_iterator it = listCommands.begin(); it != listCommands.end(); ++it)
	{
		//std::list<CommandBase*>::const_iterator prev = it;
		(*it)->execute();
		/*
		if (prev == it)
		{
			++it;
		}
		//*/
	}

	listCommands.clear();
}
