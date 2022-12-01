#pragma once
#include "../src/Scene.h"
#include "Frigate.h"
#include "WorldPlane.h"
#include "EnemyTank.h"
#include "EnemyFighter.h"
#include "PlayerTank.h"
#include "PlayerTurret.h"
#include "SpriteTest.h"
#include "TreeTrunk.h"
#include "Rock.h"
#include "Ruins.h"
#include "Powerup.h"
#include "../src/Terrain.h"

#include "GameManager.h"
#include "Player2Tank.h"
#include "Player2Turret.h"
class SceneTankBattle : public Scene
{
public:
	SceneTankBattle() = default;
	~SceneTankBattle() = default;

	PlayerTank* player;
	Player2Tank* player2;
	WorldPlane* worldPlane;

	//Terrain* terrain;

	Powerup* healPower;
	Powerup* healPower2;
	Powerup* healPower3;
	Powerup* speedPower;
	Powerup* speedPower2;
	Powerup* damagePower;

	void IdentifyTerrainCells(Vect pos, float radius);
	


	//std::list<EnemyTank*> enemies;
	//TreeTrunk* trees[100];

	static const int tankIncrease = 1;
	static int numEnemies;
	int remainingTanks;

	static int numFighters;

	int numTrees = 50;
	int numRocks = 100;
	int numRuins = 15;

	void DrawHUD();

	void Initialize();
	void SceneEnd();

	void UpdateRemainingTanks();

	void SetCollisions();
private:
	float timeStart;

};