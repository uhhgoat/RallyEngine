#include "GameManager.h"
#include "EnemyTank.h"
#include "EnemyFighter.h"
#include "TreeTrunk.h"
#include "Rock.h"
#include "Ruins.h"

GameManager* GameManager::ptrInstance = nullptr;

GameManager::GameManager()
{
	// Spritefont Test
	fonttest = SpriteFontManager::Get("agency");
	TANKS = new SpriteString(fonttest, " Tanks Remaining", 50, Rally::GetHeight() - 50);
	SCORE = new SpriteString(fonttest, "SCORE: ", 500, Rally::GetHeight() - 50);
	GAME_TIME = new SpriteString(fonttest, "TIME", 500, 50);
}

void GameManager::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

int GameManager::GetScore()
{
	return Instance().score;
}

void GameManager::AddScore(int s)
{
	Instance().score += s;
}

int GameManager::GetLevel()
{
	return Instance().levelnum;
}

void GameManager::AddLevel()
{
	Instance().levelnum += 1;
}

SpriteString* GameManager::GetEnemiesSS()
{
	return Instance().TANKS;
}

SpriteString* GameManager::GetScoreSS()
{
	return Instance().SCORE;
}

SpriteString* GameManager::GetGameTimeSS()
{
	return Instance().GAME_TIME;
}

void GameManager::Clear()
{
	for (auto&& child : Instance().enemies) {
		delete child.second;
	}
	Instance().enemies.clear();

	for (auto&& child : Instance().fighters) {
		delete child.second;
	}
	Instance().fighters.clear();

	for (auto&& child : Instance().trees) {
		delete child.second;
	}
	Instance().trees.clear();

	for (auto&& child : Instance().rocks) {
		delete child.second;
	}
	Instance().rocks.clear();

	for (auto&& child : Instance().ruins) {
		delete child.second;
	}
	Instance().ruins.clear();
}

void GameManager::AddEnemy(EnemyTank* enemy, int ID)
{
	Instance().enemies[ID] = enemy;
}

EnemyTank* GameManager::GetEnemy(int ID)
{
	return Instance().enemies[ID];
}

void GameManager::AddFighter(EnemyFighter* enemy, int ID)
{
	Instance().fighters[ID] = enemy;
}

EnemyFighter* GameManager::GetFighter(int ID)
{
	return Instance().fighters[ID];;
}

void GameManager::AddTree(TreeTrunk* tree, int ID)
{
	Instance().trees[ID] = tree;
}

TreeTrunk* GameManager::GetTree(int ID)
{
	return Instance().trees[ID];
}

void GameManager::AddRock(Rock* rock, int ID)
{
	Instance().rocks[ID] = rock;
}

Rock* GameManager::GetRock(int ID)
{
	return Instance().rocks[ID];
}

void GameManager::AddRuins(Ruins* ruins, int ID)
{
	Instance().ruins[ID] = ruins;
}

Ruins* GameManager::GetRuins(int ID)
{
	return Instance().ruins[ID];
}

GameManager::~GameManager()
{
	for (auto&& child : enemies) {
		delete child.second;
	}

	for (auto&& child : fighters) {
		delete child.second;
	}

	for (auto&& child : trees) {
		delete child.second;
	}

	for (auto&& child : rocks) {
		delete child.second;
	}

	for (auto&& child : ruins) {
		delete child.second;
	}

	delete TANKS;
	delete SCORE;
	delete GAME_TIME;
}
