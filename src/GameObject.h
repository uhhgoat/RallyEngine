#pragma once
#include "Updatable.h"
#include "Drawable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "Collidable.h"
#include "AzulCore.h"
#include "Visualizer.h"
class GameObjectEntryCommand;
class GameObjectExitCommand;

class GameObject : public Updatable, public Drawable, public Alarmable, public Inputable, public Collidable
{
	friend class GameObjectAttorney;

public:
	void SubmitEntry();
	void SubmitExit();
	GameObject();
	~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
private:
	RegistrationState currState;
	GameObjectEntryCommand* pRegCmd;
	GameObjectExitCommand* pDeregCmd;

	bool inScene;

	void ConnectToScene();
	void DisconnectFromScene();
	virtual void SceneEntry() {};
	virtual void SceneExit() {};
};