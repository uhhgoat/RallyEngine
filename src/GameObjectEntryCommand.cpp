#include "GameObjectEntryCommand.h"
#include "GameObjectAttorney.h"
GameObjectEntryCommand::GameObjectEntryCommand(GameObject* go)
	:ptrGO(go)
{

}
void GameObjectEntryCommand::execute()
{
	GameObjectAttorney::Registration::SceneEntry(ptrGO);
}