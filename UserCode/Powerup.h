#pragma once
#include "../src/GameObject.h"
#include "../src/Rally.h"
#include "PlayerTank.h"
class PlayerTank;
class Player2Tank;

enum class POWERUP_TYPE
{
	HEALTH,
	SPEED,
	DAMAGE
};

class Powerup : public GameObject, public Align16
{
public:


	Powerup(float x, float y, POWERUP_TYPE _type);
	~Powerup();
	virtual void Update();
	virtual void Draw();
	virtual void Collision(PlayerTank* tank);
	virtual void Collision(Player2Tank* tank);

	POWERUP_TYPE type;

private:
	float scale = 15.0f;
	Matrix Scale;
	Matrix Rot;
	Vect Pos;
	GraphicsObject_WireframeConstantColor* pGObj_Powerup;
	bool BsphereToggle = true;
	Vect color;


};