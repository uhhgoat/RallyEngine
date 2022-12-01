#include "MenuItem.h"

MenuItem::MenuItem()
{
	image = nullptr;
	imageFocus = nullptr;
	string = new SpriteString(SpriteFontManager::Get("agency"), "", 0, 0);
	hide = false;
	focus = false;
	Up = nullptr;
	Down = nullptr;
	Left = nullptr;
	Right = nullptr;
}

MenuItem::~MenuItem()
{
	delete image;
	delete imageFocus;
	delete string;
}

void MenuItem::SetString(std::string s)
{
	string->Set(s);
}

void MenuItem::SetImage(Image* i)
{
	image->SetImage(i);
}

void MenuItem::SetFocusImage(Image* i)
{
	imageFocus->SetImage(i);
}

void MenuItem::SetPosition(float angle, float _x, float _y, float scalex, float scaley, float cx, float cy)
{
	x = _x;
	y = _y;
	if (string != nullptr)
		string->Set((int)x, (int)y);
	if (image != nullptr)
	{
		image->SetAngle(angle);
		image->SetCenter(cx, cy);
		image->SetScalePixel(scalex, scaley);
		image->SetPosition(x, y);
	}
	if (imageFocus != nullptr)
	{
		imageFocus->SetAngle(angle);
		imageFocus->SetCenter(cx, cy);
		imageFocus->SetScalePixel(scalex, scaley);
		imageFocus->SetPosition(x, y);
	}
}

void MenuItem::Render()
{
	if (!hide)
	{
		if (focus)
		{
			if (imageFocus != nullptr)
				imageFocus->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera());
		}
		else
		{
			if (image != nullptr)
				image->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera());
		}
		if (string != nullptr)
			string->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera());
	}
}

void MenuItem::SetFocus(bool f)
{
	focus = f;
}
