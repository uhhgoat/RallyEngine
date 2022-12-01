#pragma once
#include "../src/GameObject.h"
#include "../src/Rally.h"
#include "SpriteTest.h"
class Bullet;
class EnemyTank;
class EnemyFighter;
class SceneTankBattle;
class Powerup;
class PlayerTurret;
class TreeTrunk;
class Ruins;
class Rock;

class PlayerTank : public GameObject, public Align16
{
public:


	PlayerTank();
	~PlayerTank();
	virtual void Update();
	virtual void Draw();
	virtual void Draw2D();
	virtual void KeyPressed(AZUL_KEY k);
	virtual void KeyDown(AZUL_KEY k);
	virtual void KeyReleased(AZUL_KEY k);
	virtual void Collision(Bullet* bullet);
	virtual void Collision(EnemyTank* tank);
	virtual void Collision(EnemyFighter* tank);
	virtual void Collision(TreeTrunk* tree);
	virtual void Collision(Ruins* ruins);
	virtual void Collision(Rock* rock);
	virtual void Collision(Powerup* power);

	Vect GetPos();
	float hitpoints = 3;
	std::list<SpriteTest*> hearts;
	std::list<SpriteTest*> heartsLost;

	SceneTankBattle* currentScene;
	static int score;
	static int playerID;
	Matrix world;

	void SetSpeed(float _speed);
	void ResetSpeed();

	void TakeDamage();
	PlayerTurret* turret;
private:
	// Tank vars
	Matrix ShipScale;

	Matrix ShipRot;
	Vect ShipPos;
	Vect PrevPos;

	//Matrix TurretRot;
	//Matrix adjustedTurretRot;
	//Vect TurretPos;

	const float scale = 1.0f;
	const float ShipRotAng = .0075f;
	float ShipTransSpeed = 0.45f;
	float speed;
	GraphicsObject_ColorNoTextureLight* pGObj_Tank;
	//GraphicsObject_TextureLight* pGObj_Tank;
	bool BsphereToggle = false;

	

	void Heal();
};