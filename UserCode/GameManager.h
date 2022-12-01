#pragma once

#include "../src/SpriteString.h"
#include "../src/SpriteFontManager.h"
#include "../src/Rally.h"
#include "../src/Terrain.h"
class EnemyTank;
class TreeTrunk;
class EnemyFighter;
class Rock;
class Ruins;

class GameManager
{
public:
	enum class OBJ_TYPE
	{
		PLAYER = 0,
		TREE,
		ENEMYTANK,
		ENEMYFIGHTER,
		ROCK,
		RUINS
	};
private:
	friend class Rally;
	static GameManager* ptrInstance;

	GameManager();
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	~GameManager();


	static GameManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new GameManager;
		return *ptrInstance;
	};
	
	static void Delete();

	int score = 0;
	int levelnum = 0;

	SpriteFont* fonttest;
	SpriteString* TANKS;
	SpriteString* SCORE;
	SpriteString* GAME_TIME;

	std::map<int, TreeTrunk*> trees;
	std::map<int, EnemyTank*> enemies;
	std::map<int, EnemyFighter*> fighters;
	std::map<int, Rock*> rocks;
	std::map<int, Ruins*> ruins;

public:
	static int GetScore();
	static void AddScore(int s);
	static int GetLevel();
	static void AddLevel();
	static SpriteString* GetEnemiesSS();
	static SpriteString* GetScoreSS();
	static SpriteString* GetGameTimeSS();

	static void Clear();

	static void AddEnemy(EnemyTank* enemy, int ID);
	static EnemyTank* GetEnemy(int ID);
	static void AddFighter(EnemyFighter* enemy, int ID);
	static EnemyFighter* GetFighter(int ID);
	static void AddTree(TreeTrunk* enemy, int ID);
	static TreeTrunk* GetTree(int ID);
	static void AddRock(Rock* rock, int ID);
	static Rock* GetRock(int ID);
	static void AddRuins(Ruins* ruins, int ID);
	static Ruins* GetRuins(int ID);
};
