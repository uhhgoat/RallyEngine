#include "Menu.h"

Menu::Menu()
{
	focus = nullptr;
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_UP, EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_DOWN, EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_LEFT, EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_RIGHT, EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ENTER, EVENT_TYPE::KEY_PRESS);
	Drawable::SubmitDrawRegistration();
}

void Menu::Add(MenuItem* item)
{
	items.push_back(item);
	if (focus == nullptr)
	{
		focus = item;
		focus->SetFocus(true);
	}
}

void Menu::SetFocus(MenuItem* item)
{
	focus = item;
	focus->SetFocus(true);
}

void Menu::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_ARROW_UP:
	{
		if (focus->Up != nullptr)
		{
			focus->SetFocus(false);
			focus = focus->Up;
			focus->SetFocus(true);
		}
		break;
	}
	case AZUL_KEY::KEY_ARROW_DOWN:
	{
		if (focus->Down != nullptr)
		{
			focus->SetFocus(false);
			focus = focus->Down;
			focus->SetFocus(true);
		}
		break;
	}
	case AZUL_KEY::KEY_ARROW_LEFT:
	{
		if (focus->Left != nullptr)
		{
			focus->SetFocus(false);
			focus = focus->Left;
			focus->SetFocus(true);
		}
		break;
	}
	case AZUL_KEY::KEY_ARROW_RIGHT:
	{
		if (focus->Right != nullptr)
		{
			focus->SetFocus(false);
			focus = focus->Right;
			focus->SetFocus(true);
		}
		break;
	}
	case AZUL_KEY::KEY_ENTER:
	{
		try
		{
			focus->Action();
		}
		catch (std::exception e)
		{
			DebugMsg::out("No Current Focus");
		}
		break;
	}
	default:
		break;
	}
}

void Menu::Draw2D()
{
	for (MenuItem* i : items)
	{
		i->Render();
	}
}

Menu::~Menu()
{
	for (MenuItem* i : items)
	{
		delete i;
	}
}
