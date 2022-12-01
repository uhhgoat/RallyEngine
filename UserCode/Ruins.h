#pragma once
#include "../src/GameObject.h"
#include "../src/Rally.h"
#include "PlayerTank.h"
class Bullet;
class PlayerTank;
class EnemyTank;
class EnemyFighter;

class Ruins : public GameObject, public Align16
{
public:


	Ruins(float x, float y, int id);
	~Ruins();
	virtual void Update();
	virtual void Draw();
	virtual void Collision(Bullet* bullet);
	virtual void Collision(EnemyFighter* tank) { AZUL_UNUSED(tank); };
	virtual void Collision(PlayerTank* tank) { AZUL_UNUSED(tank); };
	virtual void Collision(EnemyTank* tank) { AZUL_UNUSED(tank); };

	int ID;
	Matrix world;
	bool transSent = false;

private:
	// Spaceship vars
	const float scale = 10.0f;
	Matrix ShipScale;
	Matrix ShipRot;
	Vect ShipPos;
	GraphicsObject_TextureLight* pGObj_Tank;
	bool BsphereToggle = true;
	Vect color;


};