/*! \page startdemo Getting Started

\section setup Setup
To begin creating a scene, first start with some initial setup. \n
Create three cpp files: GameInitialize, GameEnd, and LoadResources. \n
These files will communicate with the engine methods to do some setup for you. \n
GameInitialize and GameEnd will be used to create and destroy your graphical setup \n

\code
#include "../src/EngineI.h"
void EngineI::GameInitialize()
{
	this->setWindowName("Matrices and Movement");
	this->setWidthHeight(800, 600);
	this->SetClearColor(0.4f, 0.4f, 0.8f, 1.0f);
}
\endcode
\code
#include "../src/EngineI.h"
void EngineI::GameEnd()
{

}
\endcode
\n
LoadResources is used to load your assets and initialize your scene and Camera.
\n
\code
#include "../src/EngineI.h"
#include "MyScene.h"
void EngineI::LoadResources()
{
	//---------------------------------------------------------------------------------------------------------
	// Load Models
	//---------------------------------------------------------------------------------------------------------
	ModelManager::Load("axis", "Axis.azul");
	ModelManager::Load("plane", "Plane.azul");
	ModelManager::Load("space_frigate_mod", "space_frigate.azul");
	ModelManager::Load("sphere", Model::PreMadedeModels::UnitSphere);

	//---------------------------------------------------------------------------------------------------------
	// Load Textures
	//---------------------------------------------------------------------------------------------------------
	TextureManager::Load("grid", "grid.tga");
	TextureManager::Load("space_frigate_tex", "space_frigate.tga");

	//---------------------------------------------------------------------------------------------------------
	// Load Shaders
	//---------------------------------------------------------------------------------------------------------
	ShaderManager::Load("textureFlatRender", "textureFlatRender");
	ShaderManager::Load("textureLightRender", "textureLightRender");
	ShaderManager::Load("colorConstantRender", "colorConstantRender");
	ShaderManager::Load("colorNoTextureRender", "colorNoTextureRender");

	//---------------------------------------------------------------------------------------------------------
	// Load the Images
	//---------------------------------------------------------------------------------------------------------
	ImageManager::Load("heart", TextureManager::Get("heart"));

	//---------------------------------------------------------------------------------------------------------
	// Load the Fonts
	//---------------------------------------------------------------------------------------------------------
	SpriteFontManager::Load("agency", "Agency");

	//---------------------------------------------------------------------------------------------------------
	// Set the next Scene to be loaded up
	//---------------------------------------------------------------------------------------------------------
	SceneManager::SetNextScene(new SceneTankBattle());


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

	SceneManager::GetCurrentScene()->GetCameraManager()->SetOrientAndPos(up3DCam, lookAt3DCam, pos3DCam);
	SceneManager::GetCurrentScene()->GetCameraManager()->UpdateCamera();

}
\endcode
\n
\section scene Creating a Scene
Next, you should create a scene. \n
The scene should derive from the engine's Scene class and will need to hold any game objects you wish to have in your scene
\n
\code
#include "../src/Scene.h"
#include "Player.h"
#include "WorldPlane.h"
#include "EnemyShip.h"
class MyScene : public Scene
{
public:
	Player *player;
	WorldPlane *worldPlane;

	void Initialize();
	void SceneEnd();
};
\endcode
\n
The scene must also define the methods Initialize and SceneEnd. \n
Initialize will instantiate your game objects
\n
\code
void SceneDemo::Initialize()
{
	//---------------------------------------------------------------------------------------------------------
	// Graphics Objects
	//---------------------------------------------------------------------------------------------------------
	player = new Player();
	worldPlane = new WorldPlane();
}
\endcode
\n
SceneEnd will delete your game objects
\n
\code
void SceneDemo::SceneEnd()
{
	delete player;
	delete worldPlane;
}
\endcode
\n
\section objects Filling your Scene
Finally, you must create the game objects which you want to see in your scene. \n
Your game objects should derive from GameObject and from Align16
\n
\code
#include "../src/GameObject.h"
class Player : public GameObject, public Align16
{
public:
	Player();
	virtual void Update();
	virtual void Draw();

private:
	Matrix scale;
	Matrix rot;
	Vect pos;
	const float speed = 1;
	const float rotAng = .05f;
	GraphicsObject_TextureLight *pGObj_SpaceFrigateLight;
};
\endcode
\n
Initialize your object as you want it. \n
\n
\code

Player::Player()
{
	scale.set(SCALE, 0.5f, 0.5f, 0.5f);
	pos.set(0, 20, 0);
	rot.set(IDENTITY);

	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	//Use the Model, Shader, and Texture Managers to retrieve the assets previously stored
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::Get("space_frigate_mod"),
	ShaderManager::Get("textureLightRender"),
	TextureManager::Get("space_frigate_tex"),
	LightColor, LightPos);

	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	//Register your object to be Updated and Drawn as needed
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

}
\endcode
\n
Define the Update and Draw of your object
\n
\code
void Player::Update()
{
	pos += Vect(0, 0, 1) * rot * speed;

	rot *= Matrix(ROT_Y, -rotAng);

	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGObj_SpaceFrigateLight->SetWorld(world);
}
\endcode
\n
\code
void Player::Draw()
{
	pGObj_SpaceFrigateLight->Render(CameraManager::GetCurrentCamera());
}
\endcode
\n
Once all of this is complete, you should have a working scene that processes movement and draws it accordingly.
\n
\n
\n


*/