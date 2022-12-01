#pragma once
#include "../src/Scene.h"
#include "../src/Menu.h"
#include "SinglePlayerButton.h"
#include "HostGameButton.h"
#include "JoinGameButton.h"
#include "CancelOnlineButton.h"
#include "StartOnlineButton.h"
#include "Title.h"
#include "Status.h"
class MainMenuScene : public Scene
{
public:

	void Initialize();
	void SceneEnd();

	virtual void NotifyClientConnect(bool success) override;
	virtual void NotifyConnectToHost(bool success) override;
	virtual void NotifyClientDisconnected() override;
	virtual void NotifyHostDisconnected() override;

private:
	Menu* mainMenu;						//Menu to contain menu items
	SinglePlayerButton* singlePlayer;	//Button to begin game solo
	HostGameButton* hostCoop;			//Button to host online lobby
	JoinGameButton* joinCoop;			//Button to join online lobby
	CancelOnlineButton* Cancel;			//Button to cancel online play
	StartOnlineButton* Start;			//Button to start online play
	Title* title;						//Just game title
	Status* status;						//String telling you status(ex.“HOSTING LOBBY”)


};