#include "SceneChangeCommand.h"
#include "SceneManager.h"
void SceneChangeCommand::execute()
{
	SceneManager::Instance().privSetNextScene(scene);
}
SceneChangeCommand::SceneChangeCommand(Scene* sc)
	:scene(sc)
{

}