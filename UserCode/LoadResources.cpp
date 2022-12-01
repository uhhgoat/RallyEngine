#include "../src/Rally.h"
#include "SceneFrigate.h"
#include "SceneTankBattle.h"
#include "MainMenuScene.h"
void Rally::LoadResources()
{
	//---------------------------------------------------------------------------------------------------------
	// Load the Models
	//---------------------------------------------------------------------------------------------------------

	// Model from file ( .azul format)
	ModelManager::Load("axis", "Axis.azul");
	ModelManager::Load("plane", 1000, 100, 100);
	ModelManager::Load("space_frigate_mod", "space_frigate.azul");
	ModelManager::Load("tank_mod", "T72.azul");
	ModelManager::Load("t99body", "t99body.azul");
	ModelManager::Load("t99turret", "t99turret.azul");
	ModelManager::Load("tank1", "tank1.azul");
	ModelManager::Load("bullet", "bullet_case.azul");
	ModelManager::Load("tree", "tree.azul");
	ModelManager::Load("heart", "heart.azul");
	ModelManager::Load("arrow", "arrow.azul");
	ModelManager::Load("rock", "rock.azul");
	ModelManager::Load("ruins", "ruins.azul");
	ModelManager::Load("fighter", "fighter.azul");


	//---------------------------------------------------------------------------------------------------------
	// Load the Textures
	//---------------------------------------------------------------------------------------------------------

	// Direct loads
	TextureManager::Load("grid", "seamless.tga");
	TextureManager::Load("grass", "grass.tga");
	TextureManager::Load("grasstoon", "grasstoon.tga");
	TextureManager::Load("space_frigate_tex", "space_frigate.tga");
	TextureManager::Load("tank_green", 45, 115, 0);
	TextureManager::Load("tank_brown", 120, 100, 65);
	TextureManager::Load("heart", "pixelHeart.tga");
	TextureManager::Load("tank1", "tank1.tga");
	TextureManager::Load("body", "body.tga");
	TextureManager::Load("tank_tex", "tank_tex.tga");
	TextureManager::Load("bullet", "bullet_tex.tga");
	TextureManager::Load("tree", "tree.tga");
	TextureManager::Load("ruins", "ruins.tga");
	TextureManager::Load("rock", "rock.tga");
	TextureManager::Load("fighter", "fighter.tga");
	TextureManager::Load("MenuItem", "menuimg.tga");
	TextureManager::Load("MenuItemFocus", "menuimgfocus.tga");
	//TextureManager::Load("MenuImage", "menuimg.tga");
	//TextureManager::Load("MenuImageFocus", "menuimgfocus.tga");

	//---------------------------------------------------------------------------------------------------------
	// Load the Images
	//---------------------------------------------------------------------------------------------------------
	ImageManager::Load("heart", TextureManager::Get("heart"));
	ImageManager::Load("MenuItem", TextureManager::Get("MenuItem"));
	ImageManager::Load("MenuItemFocus", TextureManager::Get("MenuItemFocus"));	

	//---------------------------------------------------------------------------------------------------------
	// Load the Shaders
	//---------------------------------------------------------------------------------------------------------
	ShaderManager::Load("textureFlatRender", "textureFlatRender");
	ShaderManager::Load("textureLightRender", "textureLightRender");
	ShaderManager::Load("colorConstantRender", "colorConstantRender");
	ShaderManager::Load("colorNoTextureRender", "colorNoTextureRender");
	ShaderManager::Load("colorNoTextureLight", "colorNoTextureLightRender");
	ShaderManager::Load("spriteRender", "spriteRender");

	//---------------------------------------------------------------------------------------------------------
	// Load the Terrain
	//---------------------------------------------------------------------------------------------------------
	TerrainObjectManager::Load("terrain", "hills2.tga", 10000, 750, -10, "grasstoon", 100, 100);
	

	//---------------------------------------------------------------------------------------------------------
	// Load the Fonts
	//---------------------------------------------------------------------------------------------------------
	SpriteFontManager::Load("agency", "Agency");
	

	//SceneManager::SetStartScene(new SceneFrigate());
	//SceneManager::SetStartScene(new SceneTankBattle());
	//SceneManager::SetNextScene(new SceneTankBattle());
	SceneManager::SetNextScene(new MainMenuScene());


	//---------------------------------------------------------------------------------------------------------
	// Setup the current 3D perspective Camera
	//---------------------------------------------------------------------------------------------------------

	SceneManager::GetCurrentScene()->GetCameraManager()->SetCurrentCamera(Camera::Type::PERSPECTIVE_3D);
	SceneManager::GetCurrentScene()->GetCameraManager()->SetViewport(0, 0, this->getWidth(), this->getHeight());
	SceneManager::GetCurrentScene()->GetCameraManager()->SetPerspective(35.0f, float(this->getWidth()) / float(this->getHeight()), 1.0f, 5000.0f);

	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	//pCam3D->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	//pCam3D->updateCamera();  // Note: if the camera moves/changes, we need to call update again

	SceneManager::GetCurrentScene()->GetCameraManager()->SetOrientAndPos(up3DCam, lookAt3DCam, pos3DCam);
	SceneManager::GetCurrentScene()->GetCameraManager()->UpdateCamera();
}