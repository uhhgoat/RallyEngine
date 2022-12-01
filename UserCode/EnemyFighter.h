#pragma once
#include "../src/GameObject.h"
#include "../src/Rally.h"
#include "PlayerTank.h"
#include "Player2Tank.h"
class Bullet;
class TreeTrunk;
class Ruins;
class Rock;

class EnemyFighter : public GameObject, public Align16
{
public:
	enum class STATE
	{
		OBSTACLE = -1,
		PURSUE = 1
	};

	EnemyFighter(float x, float y, int id);
	~EnemyFighter();
	virtual void Update();
	virtual void Draw();
	//virtual void Alarm0();
	virtual void Alarm1();
	virtual void KeyPressed(AZUL_KEY k);
	virtual void KeyReleased(AZUL_KEY k);
	virtual void Collision(Bullet* bullet);
	virtual void Collision(PlayerTank* tank);
	virtual void Collision(TreeTrunk* tree);
	virtual void Collision(Ruins* ruins);
	virtual void Collision(Rock* rock);
	SceneTankBattle* currentScene;

	int ID;
	Matrix world;
	STATE state;

private:
	// Spaceship vars
	const float scale = 3;
	Matrix ShipScale;
	Matrix ShipRot;
	Matrix adjustedRot;
	Matrix RotOff;
	Vect ShipPos;
	float speed;
	const float ShipTransSpeed = 0.5f;
	const float ShipSlowSpeed = 0.20f;
	const float ShipRotAng = .005f;
	float ShipRotDir = 1.0f;
	Vect PlaneNormal;
	int planeDist = 5;
	GraphicsObject_TextureLight* pGObj_Tank;
	//GraphicsObject_WireframeConstantColor* pGObj_TankBSphere;
	bool BsphereToggle = true;
	Vect color;


	bool lineOfSight = false;

	PlayerTank* target;
	Player2Tank* target2;

	//GAMEPLAY RELATED
	float hitpoints;
	int fireRate;
	bool inRange = false;
	int range = 250;

	void TakeDamage(float damage);


};