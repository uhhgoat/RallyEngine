#pragma once
#include <map>
#include <string>
#include "ShaderObject.h"
#include <list>
#include "SpriteFont.h"
#include "SpriteString.h"

class ScreenLog
{
private:
	friend class Rally;
	static ScreenLog* ptrInstance;

	ScreenLog();
	ScreenLog(const ScreenLog&) = delete;
	ScreenLog& operator=(const ScreenLog&) = delete;
	~ScreenLog();

	int anchorX;
	int anchorY;

	char DebugBuff[265];

	SpriteFont* font;
	
	using MessageCollection = std::list<std::string>;
	using SpriteStringCollection = std::list<SpriteString*>;

	MessageCollection messages;
	SpriteStringCollection ssmessages;

	static ScreenLog& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ScreenLog;
		return *ptrInstance;
	};

	static void Render();

	static void Delete();
public:

	static void Add(char* A, ...);

};
