/*! \page menudemo Creating Menus

\section menusetup Menu Setup
Menus can be made using Menu and MenuItem classes. A Menu is a container that holds MenuItems and can be \n
manipulated to control what is selected and pressed. \n
The Menu class is not an object, but it is drawable and Inputable so that the information can be diplayed, \n
and the arrow keys and 'enter' key can be used as controls. \n
\n
A menu can be contained on it's own scene, though it does not have to be. To start using it, create a Menu in the scene. \n
\n
\code
void MainMenuScene::Initialize()
{
	mainMenu = new Menu();
	...
}
\endcode
\n
\section menuitems Creating Menu Items
A MenuItem is a node with an action associated with it, as well as accessors to its adjacent nodes. \n
A MenuItem has pointers to its up, down, left, and right nodes. They also have an action method which needs to be defined. \n
You can set both a string of text as well as two background images for each MenuItem. One default and one for selected (focus). \n
To create your own MenuItems, you must make a class that derives from MenuItem. \n
\code
class SinglePlayerButton : public MenuItem
{
public:
	SinglePlayerButton()
	{
		string->Set("Solo Game");
		image = new RallySprite();
		imageFocus = new RallySprite();
		image->SetImage(ImageManager::Get("MenuItem"));
		imageFocus->SetImage(ImageManager::Get("MenuItemFocus"));
	}
	virtual void Action() override
	{
		DoSomething();
	};
};
\endcode
\n
\section menupop Populating Your Menu
Once you have made all of the menu items you want, you can begin adding them to your menu. \n
You must create the MenuItem in the scene, and add it to the Menu. Be sure to set the Up, Down, Left, or Right \n
values in the scene to be able to adjust focus. The first MenuItem added will be the default Focus. \n
\n
\code
	singlePlayer = new SinglePlayerButton();
	singlePlayer->SetPosition(0, 50, (float)Rally::GetHeight() - 200, 300, 100, 150, 0);

	hostCoop = new HostGameButton();
	hostCoop->SetPosition(0, 50, (float)Rally::GetHeight() - 300, 300, 100, 150, 0);

	joinCoop = new JoinGameButton();
	joinCoop->SetPosition(0, 50, (float)Rally::GetHeight() - 400, 300, 100, 150, 0);

	singlePlayer->Down = hostCoop;
	hostCoop->Up = singlePlayer;
	hostCoop->Down = joinCoop;
	joinCoop->Up = hostCoop;

	mainMenu->Add(singlePlayer);
	mainMenu->Add(hostCoop);
	mainMenu->Add(joinCoop);
\endcode
\n
\section menuend Use and Cleanup
Once the scene is running, you can use the arrow keys to adjust the current focus, and the 'enter' key \n
to trigger the Action method of the MenuItem currently in focus. \n
On SceneEnd, be sure to delete the Menu, and it will delete all of the MenuItems that were set in it. \n
\n
\code
void MainMenuScene::SceneEnd()
{
	delete mainMenu;
}
\endcode
\n
\n
\n
*/