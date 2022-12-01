#pragma once
#include "../src/GameObject.h"
#include "../src/Rally.h"
class EnemyTank;
class EnemyFighter;
class PlayerTank;
class PlayerTurret;
class Player2Tank;
class Player2Turret;
class TreeTrunk;
class Ruins;
class Rock;

class Bullet : public GameObject, public Align16
{
public:


	Bullet();
	Bullet(const Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;
	~Bullet();
	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();
	virtual void SceneEntry();
	virtual void SceneExit();
	virtual void Collision(EnemyTank* tank);
	virtual void Collision(EnemyFighter* tank);
	virtual void Collision(TreeTrunk* tank);
	virtual void Collision(PlayerTank* tank);
	virtual void Collision(PlayerTurret* tank);
	virtual void Collision(Player2Tank* tank);
	virtual void Collision(Player2Turret* tank);
	virtual void Collision(Ruins* tank);
	virtual void Collision(Rock* tank);
	virtual void CollisionTerrain();
	void Initialize(Matrix r, Vect m);

	const float scale = 0.125f;
	float speed = 5.0f;
	Matrix rot;
	Matrix bulletScale;
	Vect pos;
	float lifetime = 10;
	static float playerDamage;
	GraphicsObject_ColorNoTextureLight* pGObj_bullet;

	static void IncreasePlayerDamage(float amt);

};