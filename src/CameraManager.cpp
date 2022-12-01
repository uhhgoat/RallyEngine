#include "CameraManager.h"
#include "Rally.h"

CameraManager::CameraManager()
{
	DefaultCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	DefaultCamera->setViewport(0, 0, 800, 600);
	DefaultCamera->setPerspective(35.0f, 1.333f, 1.0f, 5000.0f);

	Vect defaultUp = Vect(0.0f, 1.0f, 0.0f);
	Vect defaultPos = Vect(50.0f, 50.0f, 150.0f);
	Vect defaultLookAt = Vect(0.0f, 0.0f, 0.0f);

	localUp = defaultUp;
	localLookAt = defaultLookAt;
	localCamPos = defaultPos;

	DefaultCamera->setOrientAndPosition(defaultUp, defaultLookAt, defaultPos);

	camCurrent = DefaultCamera;

	//2D Camera ------------------------------------------------------------
	cam2DCurrent = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	assert(cam2DCurrent);

	cam2DCurrent->setViewport(0, 0, Rally::GetWidth(), Rally::GetHeight());
	cam2DCurrent->setOrthographic(-0.5f * Rally::GetWidth(), 0.5f * Rally::GetHeight(), -0.5f * Rally::GetHeight(),
		0.5f * Rally::GetHeight(), 1.0f, 1000.0f);

	// Orient Camera
	Vect up2DCam(0.0f, 1.0f, 0.0f);
	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	cam2DCurrent->setOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);
	cam2DCurrent->updateCamera();
}


CameraManager::~CameraManager()
{
	bool samecams = (camCurrent == DefaultCamera);
	delete camCurrent;
	delete cam2DCurrent;
	if(!samecams)
		delete DefaultCamera;
}

Camera* CameraManager::privGet()
{
	return camCurrent;
}

Camera* CameraManager::privGet2D()
{
	return cam2DCurrent;
}

void CameraManager::privSet(Camera* newCam)
{
	camCurrent = newCam;
}

void CameraManager::privSet(Camera::Type camType)
{
	camCurrent = new Camera(camType);
}

void CameraManager::privSetOrientandPos(Vect up, Vect lookAt, Vect camPos)
{
	camCurrent->setOrientAndPosition(up, lookAt, camPos);
}
void CameraManager::privUpdateCamera()
{
	//ScreenLog::Add("Cam Pos: %3.1f, %3.1f, %3.1f", localCamPos[y], localCamPos[y], localCamPos[z]);
	switch (mode)
	{
	case CAM_MODE::STATIC:
		break;
	case CAM_MODE::FOLLOW:
		follow(localUp, localLookAt, localCamPos);
		break;
	case CAM_MODE::GOD:
		camControls();
		break;
	default:
		break;
	}
	camCurrent->updateCamera();
}

void CameraManager::follow(Vect up, Vect lookAt, Vect camPos)
{
	privSetOrientandPos(up, lookAt, camPos);
}


void CameraManager::privSetViewport(const int inX, const int inY, const int width, const int height)
{
	camCurrent->setViewport(inX, inY, width, height);
}
void CameraManager::privSetPerspective(const float fieldOfView, const float aspectRatio, const float nearDist, const float farDist)
{
	camCurrent->setPerspective(fieldOfView, aspectRatio, nearDist, farDist);
}

void CameraManager::camControls()
{
	float camSpeed = 0.75f;
	if (GetKeyState('I') & 0x08000)
	{
		TranslateFwdBack(camSpeed);
	}
	else if (GetKeyState('K') & 0x08000)
	{
		TranslateFwdBack(-camSpeed);
	}

	if (GetKeyState('J') & 0x08000)
	{
		TranslateLeftRight(-camSpeed);
	}
	else if (GetKeyState('L') & 0x08000)
	{
		TranslateLeftRight(camSpeed);
	}

	float rotSpeed = 0.005f;
	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		TurnLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		TurnLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		TiltUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		TiltUpDown(-rotSpeed);
	}

}

void CameraManager::TranslateLeftRight(float delta)
{
	Vect right;
	camCurrent->getRight(right);
	localCamPos += (right * delta);
	localLookAt += (right * delta);
	privSetOrientandPos(localUp, localLookAt, localCamPos);
}

void CameraManager::TranslateFwdBack(float delta)
{
	Vect dir;
	camCurrent->getDir(dir);
	localCamPos -= (dir * delta);
	localLookAt -= (dir * delta);
	privSetOrientandPos(localUp, localLookAt, localCamPos);
}

void CameraManager::TiltUpDown(float ang)
{
	Vect right;
	camCurrent->getRight(right);
	Matrix Rot = Matrix(ROT_AXIS_ANGLE, right, ang);
	Vect dir;
	camCurrent->getDir(dir);
	dir *= Rot;
	localUp *= Rot;
	localLookAt = localCamPos - dir;
	privSetOrientandPos(localUp, localLookAt, localCamPos);
}

void CameraManager::TurnLeftRight(float ang)
{

	Matrix Rot = Matrix(ROT_Y, ang);
	Vect dir;
	camCurrent->getDir(dir);
	dir *= Rot;
	localUp *= Rot;
	localLookAt = localCamPos - dir;
	privSetOrientandPos(localUp, localLookAt, localCamPos);
}