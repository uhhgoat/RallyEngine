#pragma once
#include "../src/GameObject.h"
#include "../src/Rally.h"

class Frigate : public GameObject, public Align16
{
public:


	Frigate();
	~Frigate();
	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();
	virtual void KeyPressed(AZUL_KEY k);
	virtual void KeyDown(AZUL_KEY k);
	virtual void KeyReleased(AZUL_KEY k);
private:
	// Spaceship vars
	Matrix ShipScale;
	Matrix ShipRot;
	Vect ShipPos;
	const float ShipTransSpeed = 1;
	const float ShipRotAng = .05f;
	GraphicsObject_TextureLight* pGObj_SpaceFrigateLight;
	GraphicsObject_WireframeConstantColor* pGObj_SpaceshipBSphere;
	bool BsphereToggle = false;
};