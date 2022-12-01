#ifndef _SpriteStringFactory
#define _SpriteStringFactory

#include <list>
#include "SpriteString.h"

class SpriteStringFactory
{
private:
	static SpriteStringFactory* ptrInstance;



	SpriteStringFactory() = default;
	SpriteStringFactory(const SpriteStringFactory&) = delete;
	SpriteStringFactory& operator=(const SpriteStringFactory&) = delete;
	~SpriteStringFactory();

	static SpriteStringFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SpriteStringFactory;
		return *ptrInstance;
	};

	std::list<SpriteString*> recycledSpriteStrings;
	std::list<SpriteString*> activeSpriteStrings;

	SpriteString* privCreateSpriteString(SpriteFont* sf, std::string s, int x, int y);
	void privRecycleSpriteString(SpriteString* b);

public:

	static SpriteString* CreateSpriteString(SpriteFont* sf, std::string s, int x, int y) { return Instance().privCreateSpriteString(sf, s, x, y); };
	static void SpriteStringReturn(SpriteString* b) { Instance().privRecycleSpriteString(b); };


	static void Terminate();
};


#endif _SpriteStringFactory