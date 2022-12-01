#pragma once
#include "GameObject.h"
#include "MenuItem.h"
class Menu : public Inputable, Drawable
{
public:
	Menu();
	~Menu();								//delete all menu items
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;

	std::list<MenuItem*> items;				//collection of menu items
	MenuItem* focus;						//current menu item selected

	/*!
	\brief Called to add MenuItem to the collection
	*/
	void Add(MenuItem* item);				//add new menu item to list
	/*!
	\brief Called to set current focus to a MenuItem
	*/
	void SetFocus(MenuItem* item);			//set the focus

	virtual void KeyPressed(AZUL_KEY k);	//check for arrows and enter

	virtual void Draw2D();					//render all items


};