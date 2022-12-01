#pragma once
#include "RallySprite.h"
class MenuItem
{
public:
	MenuItem();
	virtual ~MenuItem();
	MenuItem(const MenuItem&) = delete;
	MenuItem& operator=(const MenuItem&) = delete;

	RallySprite* image;				//texture assigned to menu item
	RallySprite* imageFocus;		//texture assigned to menu item on focus
	SpriteString* string;			//string to appear on menu item
	float x;							//screen x coordinate
	float y;							//screen y coordinate
	bool hide;						//used to hide on Render
	bool focus;

	MenuItem* Up;					//menu item above this one
	MenuItem* Down;					//menu item below this one
	MenuItem* Left;					//menu item left of this one
	MenuItem* Right;				//menu item right of this one

	/*!
	\brief Called to set the string displayed on the MenuItem
	*/
	void SetString(std::string s);	//set the sprite string string
	/*!
	\brief Called to set the Image displayed on the MenuItem
	*/
	void SetImage(Image* i);		//set the image
	/*!
	\brief Called to set the Focus Image displayed on the MenuItem
	*/
	void SetFocusImage(Image* i);		//set the image
	/*!
	\brief Called to set the position of the MenuItem
	*/
	void SetPosition(float angle, float _x, float _y, float scalex, float scaley, float cx, float cy); //set location
	/*!
	\brief Overloaded by user to define what happens when 'enter' is pressed when in focus
	*/
	virtual void Action() = 0;		//what happens when ‘enter’ is pressed
	/*!
	\brief Called to render the MenuItem
	*/
	void Render();					//render the sprite and string
	/*!
	\brief Called to set this MenuItem as the current focus
	*/
	void SetFocus(bool f);

};