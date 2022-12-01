#pragma once
#include "Camera.h"

class CameraManager
{
public:

	CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;
	~CameraManager();
private:

	Camera* camCurrent;
	Camera* DefaultCamera;
	Camera* cam2DCurrent;

	enum class CAM_MODE
	{
		STATIC,
		FOLLOW,
		GOD
	};

	CAM_MODE mode = CAM_MODE::STATIC;

	Camera* privGet();
	Camera* privGet2D();
	void privSet(Camera* newCam);
	void privSet(Camera::Type camType);

	void privSetOrientandPos(Vect up, Vect lookAt, Vect camPos);
	void privUpdateCamera();
	void privSetViewport(const int inX, const int inY, const int width, const int height);
	void privSetPerspective(const float fieldOfView, const float aspectRatio, const float nearDist, const float farDist);

	void camControls();
	void follow(Vect up, Vect lookAt, Vect camPos);
	void TranslateLeftRight(float delta);
	void TranslateFwdBack(float delta);
	void TiltUpDown(float ang);
	void TurnLeftRight(float ang);

	Vect localUp;
	Vect localLookAt;
	Vect localCamPos;

public:

	Camera* GetCurrentCamera() { return privGet(); };
	Camera* GetCurrent2DCamera() { return privGet2D(); };

	void SetCurrentCamera(Camera* newCam) { privSet(newCam); };

	void SetCurrentCamera(Camera::Type camType) { privSet(camType); };
	void SetOrientAndPos(Vect up, Vect lookAt, Vect camPos) { privSetOrientandPos(up, lookAt, camPos); };
	void UpdateCamera() { privUpdateCamera(); };
	void SetViewport(const int inX, const int inY, const int width, const int height) { privSetViewport(inX, inY, width, height); };
	void SetPerspective(const float fieldOfView, const float aspectRatio, const float nearDist, const float farDist)
	{
		privSetPerspective(fieldOfView, aspectRatio, nearDist, farDist);
	};

	void SetStatic() { mode = CAM_MODE::STATIC; }
	void SetGodCam() { mode = CAM_MODE::GOD; }
	void SetFollow() { mode = CAM_MODE::FOLLOW; }
	void UpdateFollowTarget(Vect in_up, Vect in_lookAt, Vect in_camPos)
	{ 
		if (mode == CAM_MODE::FOLLOW)
		{
			localUp = in_up;
			localLookAt = in_lookAt;
			localCamPos = in_camPos;
		}
	}
};
