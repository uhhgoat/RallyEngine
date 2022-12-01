#pragma once
#include "GameObject.h"
class GameObjectAttorney
{
public:
	class Registration
	{
	private:
		friend class GameObjectEntryCommand;
		friend class GameObjectExitCommand;
		static void SceneEntry(GameObject* obj) { obj->ConnectToScene(); };
		static void SceneExit(GameObject* obj) { obj->DisconnectFromScene(); };
	};

};