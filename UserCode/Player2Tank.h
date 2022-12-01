#pragma once
#include "../src/GameObject.h"
#include "../src/Rally.h"
#include "SpriteTest.h"
class Bullet;
class EnemyTank;
class SceneTankBattle;
class Player2Turret;
class Powerup;

class Player2Tank : public GameObject, public Align16
{
public:


	Player2Tank();
	~Player2Tank();
	virtual void Update();
	virtual void Draw();
	virtual void Draw2D();
	virtual void Collision(Bullet* bullet);
	virtual void Collision(EnemyTank* tank) { AZUL_UNUSED(tank); };
	virtual void Collision(Powerup* power) { AZUL_UNUSED(power); };

	Vect GetPos();
	float hitpoints = 3;

	SceneTankBattle* currentScene;
	static int score;
	static int playerID;
	Matrix world;

	void MoveVert(float dir);
	void Steer(float dir);
	void Aim(float dir);

	void Fire();

	void TakeDamage();
	Player2Turret* turret;

private:
	// Tank vars
	Matrix ShipScale;

	Matrix ShipRot;
	Vect ShipPos;


	const float scale = 1.0f;
	const float ShipTransSpeed = 0.45f;
	const float ShipRotAng = .0075f;
	GraphicsObject_ColorNoTextureLight* pGObj_Tank;
	//GraphicsObject_ColorNoTextureLight* pGObj_Turret;
	bool BsphereToggle = false;



};