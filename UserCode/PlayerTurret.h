#pragma once
#include "../src/GameObject.h"
#include "../src/Rally.h"
#include "SpriteTest.h"
class Bullet;
class PlayerTank;
class SceneTankBattle;

class PlayerTurret : public GameObject, public Align16
{
public:


	PlayerTurret();
	~PlayerTurret();
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

	PlayerTank* player;

	const float scale = 1.0f;
	const float ShipRotAng = .0075f;
	float ShipTransSpeed = 0.45f;
	GraphicsObject_ColorNoTextureLight* pGObj_Turret;
	bool BsphereToggle = false;

	void PlayerKilled();
};