#pragma once
#include "../src/GameObject.h"
#include "../src/Rally.h"
class WorldPlane : public GameObject
{
public:
	WorldPlane();
	~WorldPlane();
	virtual void Draw();
	virtual void Alarm0();
	virtual void Alarm1();
private:
	GraphicsObject_TextureFlat* pGObj_Plane;
	GraphicsObject_ColorNoTexture* pGObj_Axis;
};