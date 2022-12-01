/*! \page camerademo Using the Camera

\section camsetup Camera Setup
The main camera should have been set up in the LoadResources method. \n
Here you will see how to manipulate a camera. \n
The camera has 3 modes. Follow, Static, and God mode;
\n
\code
enum class CAM_MODE
{
	STATIC,
	FOLLOW,
	GOD
};
\endcode
\n
All access to the current camera must be done through the scene manager. \n
In order to set the mode, call any of the setMode methods.
\n
\code
void SetStatic() { mode = CAM_MODE::STATIC; }
void SetGodCam() { mode = CAM_MODE::GOD; }
void SetFollow() { mode = CAM_MODE::FOLLOW; }
\endcode
\n
When using Static camera, you can set the position and orientation of the camera
\n
\code
SceneManager::GetCurrentScene()->GetCameraManager()->SetOrientAndPos(Vect up, Vect lookAt, Vect camPos)
\endcode
\n
When using God Cam, you may set the position and orientation the same way. \n
When God Cam is active, you may look around with the arrow keys and move with the IJKL keys.
\n
\n
When using Follow mode, you must update the follow target in the update of a gameobject.
\n
\code
void Player::Update()
{
	Vect up = Vect(0, 1, 0);
	Vect lookAt = ShipPos + Vect(0, 25, 0);
	Vect camPos = (ShipPos + Vect(0, 50, -100) * ShipRot);
	SceneManager::GetCurrentScene()->GetCameraManager()->UpdateFollowTarget(up, lookAt, camPos);
}
\endcode

\n
\n
\n
*/