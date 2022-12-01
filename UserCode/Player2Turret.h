#pragma once
#include "../src/GameObject.h"
#include "../src/Rally.h"
#include "SpriteTest.h"
class Bullet;
class Player2Tank;
class SceneTankBattle;

class Player2Turret : public GameObject, public Align16
{
public:


	Player2Turret();
	~Player2Turret();
	virtual void Update();
	virtual void Draw();
	virtual void Collision(Bullet* bullet);

	//Vect GetPos();

	// Tank vars
	Matrix ShipScale;

	Matrix TurretRot;
	Matrix adjustedTurretRot;
	Vect TurretPos;

	SceneTankBattle* currentScene;

	Player2Tank* player2;

	const float scale = 1.0f;
	const float ShipRotAng = .0075f;
	float ShipTransSpeed = 0.45f;
	GraphicsObject_ColorNoTextureLight* pGObj_Turret;
	bool BsphereToggle = false;

	void Player2Killed();
};