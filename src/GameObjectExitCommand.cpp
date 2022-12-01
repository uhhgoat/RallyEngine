#include "GameObjectExitCommand.h"
#include "GameObjectAttorney.h"
GameObjectExitCommand::GameObjectExitCommand(GameObject* go)
	:ptrGO(go)
{

}
void GameObjectExitCommand::execute()
{
	GameObjectAttorney::Registration::SceneExit(ptrGO);
}