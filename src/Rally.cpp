#include "AzulCore.h"
#include "Rally.h"
#include "VisualizerAttorney.h"

Rally* Rally::ptrInstance = nullptr;


//-----------------------------------------------------------------------------
// Rally::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Rally::Initialize()
{
	GameInitialize();
}

void Rally::Delete()
{
	TimeManager::Delete();
	delete ptrInstance;
	ptrInstance = nullptr;
}

//-----------------------------------------------------------------------------
// Rally::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Rally::LoadContent()
{
	this->LoadResources();

	SceneManager::InitStartScene();
}

//-----------------------------------------------------------------------------
// Rally::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Rally::Update()
{
	TimeManagerAttorney::ProcessTime(this->GetTimeInSeconds());

	NetworkManager::ProcessOutputQueue();

	SceneManager::Update();

	NetworkManager::ProcessInputQueue();
}

//-----------------------------------------------------------------------------
// Rally::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Rally::Draw()
{
	//ScreenLog::Add("TEST LOG");
	SceneManager::Draw();

	VizualizerAttorney::GameLoop::VisualizeAll();


	ScreenLog::Render();
}


int Rally::privGetWidth()
{
	return this->getWidth();
}
int Rally::privGetHeight()
{
	return this->getHeight();
}
float Rally::privGetTime()
{
	return this->GetTimeInSeconds();
}
void Rally::privSetClear(float red, float green, float blue, float alpha)
{
	this->SetClearColor(red, green, blue, alpha);
}
void Rally::privSetWidthHeight(int width, int height)
{
	this->setWidthHeight(width, height);
}
void Rally::privSetWindowName(const char* name)
{
	this->setWindowName(name);
}



//-----------------------------------------------------------------------------
// Rally::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Rally::UnLoadContent()
{
	GameEnd();
	// general clean up.
	SceneManager::Delete();
	//CameraManager::Delete();
	Visualizer::Delete();
	ModelManager::Delete();
	ShaderManager::Delete();
	TextureManager::Delete();
	ImageManager::Delete();
	SpriteFontManager::Delete();
	NetworkManager::Delete();
	ScreenLog::Delete();
	TerrainObjectManager::Delete();
}
