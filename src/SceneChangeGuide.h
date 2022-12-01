/*! \page scenechange Changing Scenes

\section changescene Change Scene
To change scenes, you must use the SceneManager to swap out your current scene. \n
You will also need to use the GameObject's Scene Entry and Exit commands to ensure proper cleanup of objects. \n
Swapping the scene is simple, just call SetNextScene.
\n
\code
	SceneManager::SetNextScene(new MyScene());
\endcode
\n
\section gameobjectcleanup GameObject Cleanup
In order to clean up game objects properly before changing scenes, define the virtual methods SceneEntry and SceneExit
in your game object. \n
Move all registration from the constructor to the SceneEntry method, all Initialization to the Initialize method,
and all of the deregistration and cleanup to the SceneEntry method. \n
\code
void Bullet::Initialize(Matrix r, Vect m)
{
	rot = r;
	pos = m;
	Matrix world = rot * Matrix(TRANS, pos);
	pGObj_bullet->SetWorld(world);
}
\endcode
\code
void Bullet::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitAlarmRegistration(2, AlarmableManager::ALARM_0);
	SetCollidableGroup<Bullet>();
	SubmitCollisionRegistration();
}
\endcode
\code
void Bullet::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
}
\endcode
\n
These methods are also useful if objects will be repeatedly used, and work well with factories and recycling. \n
In your factory, initialize your object with Initialize and call its registrations by calling SubmitEntry().
\n
\code
	Bullet* b;
	b->Initialize(r, m);
	b->SubmitEntry();
\endcode

\n
\n
\n


*/