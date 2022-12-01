#include "SpriteStringFactory.h"

SpriteStringFactory* SpriteStringFactory::ptrInstance = nullptr;


SpriteString* SpriteStringFactory::privCreateSpriteString(SpriteFont* sf, std::string s, int x, int y)
{
	SpriteString* b;

	if (recycledSpriteStrings.empty())
	{

		b = new SpriteString();

	}
	else
	{

		b = recycledSpriteStrings.front();
		recycledSpriteStrings.pop_front();

	}
	activeSpriteStrings.push_front(b);
	b->Initialize(sf, s, x, y);
	return b;
}



void SpriteStringFactory::privRecycleSpriteString(SpriteString* b)
{
	b->Recycle();
	recycledSpriteStrings.push_front(b);
	activeSpriteStrings.remove(b);
}


void SpriteStringFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

SpriteStringFactory::~SpriteStringFactory()
{

	while (!recycledSpriteStrings.empty())
	{
		delete recycledSpriteStrings.front();
		recycledSpriteStrings.pop_front();
	}
	while (!activeSpriteStrings.empty())
	{
		delete activeSpriteStrings.front();
		activeSpriteStrings.pop_front();
	}
}