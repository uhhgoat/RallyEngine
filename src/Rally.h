#ifndef RALLY_H
#define RALLY_H

#include "AzulCore.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "TerrainObjectManager.h"
#include "ScreenLog.h"
#include "SpriteFontManager.h"
#include "TimeManagerAttorney.h"
#include "NetworkManager.h"
#include "RallyColors.h"

class Rally : public Engine
{
	friend class RallyAttorney;
public:
	static void Run() { Instance().run(); };
	static void Delete();

	static int GetWidth() { return Instance().privGetWidth(); };
	static int GetHeight() { return Instance().privGetHeight(); };
	static void SetClear(float red, float green, float blue, float alpha){ Instance().privSetClear(red, green, blue, alpha); };
	static void SetWidthHeight(int width, int height) { Instance().privSetWidthHeight(width, height); };
	static void SetWindowName(const char* name) { Instance().privSetWindowName(name); };


private:
	// legacy
	Rally(const char* windowName, const int Width, const int Height);

	static Rally* ptrInstance;
	Rally() = default;
	Rally(const Rally&) = delete;
	Rally& operator=(const Rally&) = delete;
	~Rally() = default;

	static Rally& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new Rally;
		return *ptrInstance;
	};

	static float GetTime() { return Instance().privGetTime(); };
	int privGetWidth();
	int privGetHeight();
	float privGetTime();
	void privSetClear(float red, float green, float blue, float alpha);
	void privSetWidthHeight(int width, int height);
	void privSetWindowName(const char* name);

	// Methods Users need to overload
	virtual void Initialize();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw();
	virtual void UnLoadContent();

	void LoadResources();
	void GameInitialize();
	void GameEnd();
};

#endif