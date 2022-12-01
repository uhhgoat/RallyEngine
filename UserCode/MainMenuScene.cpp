#include "MainMenuScene.h"
void MainMenuScene::Initialize()
{

	NetworkManager::SetProtocol(NetworkManager::PROTOCOL::TCP);

	//---------------------------------------------------------------------------------------------------------
	// Graphics Objects
	//---------------------------------------------------------------------------------------------------------
	mainMenu = new Menu();

	//create menu items, set positions
	singlePlayer = new SinglePlayerButton();
	singlePlayer->SetPosition(0, 50, (float)Rally::GetHeight() - 200, 300, 100, 150, 0);

	hostCoop = new HostGameButton();
	hostCoop->SetPosition(0, 50, (float)Rally::GetHeight() - 300, 300, 100, 150, 0);

	joinCoop = new JoinGameButton();
	joinCoop->SetPosition(0, 50, (float)Rally::GetHeight() - 400, 300, 100, 150, 0);

	Start = new StartOnlineButton();
	Start->SetPosition(0, 350, (float)Rally::GetHeight() - 300, 300, 100, 150, 0);

	Cancel = new CancelOnlineButton();
	Cancel->SetPosition(0, 350, (float)Rally::GetHeight() - 400, 300, 100, 150, 0);

	title = new Title();
	title->SetPosition(0, 50, (float)Rally::GetHeight() - 100, 300, 100, 150, 0);

	status = new Status();
	status->SetPosition(0, 50, (float)Rally::GetHeight() - 500, 300, 100, 150, 0);

	//set connections
	singlePlayer->Down = hostCoop;
	hostCoop->Up = singlePlayer;
	hostCoop->Right = Start;
	hostCoop->Down = joinCoop;
	joinCoop->Up = hostCoop;
	joinCoop->Right = Cancel;
	Start->Left = hostCoop;
	Start->Down = Cancel;
	Cancel->Up = Start;
	Cancel->Left = joinCoop;

	hostCoop->statusString = status;
	joinCoop->statusString = status;
	Start->statusString = status;
	Cancel->statusString = status;
	singlePlayer->statusString = status;

	//add to main menu
	mainMenu->Add(singlePlayer);
	mainMenu->Add(hostCoop);
	mainMenu->Add(joinCoop);
	mainMenu->Add(Start);
	mainMenu->Add(Cancel);
	mainMenu->Add(title);
	mainMenu->Add(status);
}


void MainMenuScene::SceneEnd()
{
	delete mainMenu;
}

void MainMenuScene::NotifyClientConnect(bool success)
{
	if (success)
		status->SetString("Client Connected.");
}

void MainMenuScene::NotifyConnectToHost(bool success)
{
	if (success)
		status->SetString("Connected to Host.");
	else
		status->SetString("Host not found.");
}

void MainMenuScene::NotifyClientDisconnected()
{
	status->SetString("Client disconnected, lobby cancelled.");
}

void MainMenuScene::NotifyHostDisconnected()
{
	status->SetString("Disconnected from host, try again");
}
