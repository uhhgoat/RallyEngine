/*! \page collisiondemo Adding Collision

\section colsetup Collision Setup
Collisions are a component of GameObject. To give an object Access to collision, simply derive from GameObject. \n
An object can be made to process collision with any other GameObject. \n
To start off, make sure to delcare and define the Collision method in your game object. \n
Make sure to put the object type yopu wish to collide with as the parameter. This can also be abstracted,
and you can use multiple overloads for collision with different objects.
\n
\code
#include "../src/GameObject.h"

class Bullet : public GameObject, public Align16
{
public:

	Bullet();
	virtual void Update();
	virtual void Draw();

	virtual void Collision(Player*) { DebugMsg::out("Hit Player."); };

};
\endcode
\n
In the constructor of your game object, make sure to set the collider model you wish to use for your given object. \n
When setting the collider model, be sure to select a volume type that you would like on your object. \n
Select from the VolumeType enum in Collidable. \n
\code
enum VolumeType
	{
		BSPHERE,
		AABB,
		OBB
	};
\endcode
Every collidable object has a default Bounding Sphere volume that is used for optimized collision processing. \n
In addition, you must call SetCollidableGroup<>() using your game object type, in order to register that object type as
collidable. This method is static and will only set the group once per object type. \n
For each instance, you must Submit registration to become collidable.
\n
\code
Bullet::Bullet()
{
	pGObj_bullet = new GraphicsObject <...>;

	SetColliderModel(pGObj_bullet->getModel(), , Collidable::VolumeType::OBB);

	SetCollidableGroup<Bullet>();
	SubmitCollisionRegistration();
}
\endcode
\n
At Any point during runtime, you can use the Visualizer tool to help see what collision volumes are active. \n
You may call any of the following static methods to show the wireframe of any collision volume \n
ShowCollisionVolume() is the simplest and will show the correct volume if passing in GetCollisionVolume() from a collidable \n
\n
\code
Visualizer::ShowCollisionVolume(const CollisionVolume& Vol, const Vect& col = DEFAULT_COLOR);
Visualizer::ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col = DEFAULT_COLOR);
Visualizer::ShowAABB(const CollisionVolumeAABB& AABB, const Vect& col = DEFAULT_COLOR);
Visualizer::ShowAABB(Vect min, Vect max, const Vect& col = DEFAULT_COLOR);
Visualizer::ShowOBB(const CollisionVolumeOBB& OBB, const Vect& col = DEFAULT_COLOR);
\endcode
\n
Lastly, in your Scene's Initialize, you must register collision pairs, so that the engine knows what objects
to check collision for. \n
You can use SetCollisionPair to set two different object types to collide, or SetCollisionSelf to have an object
collide with others of the same type.
\n
\code
void MyScene::Initialize()
{
	SetCollisionPair<Bullet, Player>();
	SetCollisionSelf<Bullet>();
}
\endcode
\n
\section colprocess Collision Processing
When processing collision, make sure to always keep track of your collision volume based on movements. \n
In the update method, make sure to UpdateCollisionData using your new world matrix at each frame. \n
\code
void Bullet::Update()
{
	Matrix world = <...>;
	pGObj_bullet->SetWorld(world);
	this->UpdateCollisionData(world);
}
\endcode
\n
Finally, don'f forget to Deregister your collision processing when the game object is destroyed.
\n
\code
	SubmitCollisionDeregistration();
\endcode
\n
\n
\n
*/