#include "ScreenLog.h"
#include "SpriteFontManager.h"
#include "SpriteStringFactory.h"
#include "Rally.h"

ScreenLog* ScreenLog::ptrInstance = nullptr;

ScreenLog::ScreenLog()
{
	anchorX = 50;
	anchorY = Rally::GetHeight()/2;
	font = SpriteFontManager::Get("agency");
}

void ScreenLog::Add(char* A, ...)
{
	va_list args;

	va_start(args, A);
	vsprintf_s(Instance().DebugBuff, A, args);
	va_end(args);

	std::string s(Instance().DebugBuff);
	Instance().messages.push_back(s);
	//Instance().ssmessages.push_back(SpriteStringFactory::CreateSpriteString(Instance().font, s, Instance().anchorX, Instance().anchorY));

}

void ScreenLog::Render()
{
	for (MessageCollection::iterator it = Instance().messages.begin(); it != Instance().messages.end(); it++)
	{
		SpriteString* spst = SpriteStringFactory::CreateSpriteString(Instance().font, (*it), Instance().anchorX, Instance().anchorY);
		spst->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera());
		SpriteStringFactory::SpriteStringReturn(spst);
	}
	Instance().messages.clear();
}

void ScreenLog::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


ScreenLog::~ScreenLog()
{
	//delete all entities.
	Instance().messages.clear();
	//*
	while (!messages.empty())
	{
		//delete Instance().messages.front();
		Instance().messages.pop_front();
	}
	//*/
	SpriteStringFactory::Terminate();
}