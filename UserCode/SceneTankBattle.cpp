#include "SceneTankBattle.h"
#include "BulletFactory.h"
int SceneTankBattle::numEnemies = 2;
int SceneTankBattle::numFighters = -1;
void SceneTankBattle::Initialize()
{
	GameManager::AddLevel();
	//---------------------------------------------------------------------------------------------------------
	// Graphics Objects
	//---------------------------------------------------------------------------------------------------------
	player = new PlayerTank();
	if (!(NetworkManager::getState() == NetworkManager::NetworkState::OFFLINE))
	{
		player2 = new Player2Tank();
		player2->currentScene = this;
		player2->turret->currentScene = this;
	}
	//worldPlane = new WorldPlane();
	//terrain = new Terrain("Textures/HMtest.tga", 1000, 500, -10, TextureManager::Get("grass"), 100, 100);
	SetTerrain("terrain");

	numEnemies += tankIncrease;
	numFighters += tankIncrease;

	timeStart = TimeManager::GetTime();

	remainingTanks = numEnemies + numFighters;
	//UpdateRemainingTanks();
	
	player->currentScene = this;
	player->turret->currentScene = this;

	for (int i = 0; i < numEnemies; i++)
	{
		EnemyTank* tank = new EnemyTank(float((rand() % 8000) - 4000), float((rand() % 8000) - 4000), i);
		tank->currentScene = this;
		GameManager::AddEnemy(tank, i);
	}

	for (int i = 0; i < numTrees; i++)
	{
		TreeTrunk* t = new TreeTrunk(float((rand() % 8000) - 4000), float((rand() % 8000) - 4000), i);
		GameManager::AddTree(t, i);
	}

	for (int i = 0; i < numRocks; i++)
	{
		Rock* t = new Rock(float((rand() % 8000) - 4000), float((rand() % 8000) - 4000), i);
		GameManager::AddRock(t, i);
	}

	for (int i = 0; i < numRuins; i++)
	{
		Ruins* t = new Ruins(float((rand() % 8000) - 4000), float((rand() % 8000) - 4000), i);
		GameManager::AddRuins(t, i);
	}

	for (int i = 0; i < numFighters; i++)
	{
		EnemyFighter* en = new EnemyFighter(float((rand() % 8000) - 4000), float((rand() % 8000) - 4000), i);
		en->currentScene = this;
		GameManager::AddFighter(en, i);
	}

	if (GameManager::GetLevel() > 1)
	{
		healPower = new Powerup(160, -2164, POWERUP_TYPE::HEALTH);
		healPower2 = new Powerup(501, 3577, POWERUP_TYPE::HEALTH);
		healPower3 = new Powerup(-747, 2637, POWERUP_TYPE::HEALTH);
		speedPower = new Powerup(1749, 1558, POWERUP_TYPE::SPEED);
		speedPower2 = new Powerup(-2812, 3901, POWERUP_TYPE::SPEED);
		damagePower = new Powerup(361, 729, POWERUP_TYPE::DAMAGE);
	}
	

	//*
	for (float i = 0; i < player->hitpoints; i++)
	{
		player->hearts.push_back(new SpriteTest(0, 50 + 100 * i, 50, 100));
	}
	//*/

	SetCollisions();
}

void SceneTankBattle::SetCollisions()
{
	SetCollisionPair<Bullet, EnemyTank>();

	SetCollisionPair<Bullet, PlayerTank>();

	SetCollisionPair<EnemyTank, PlayerTank>();

	SetCollisionPair<EnemyTank, TreeTrunk>();

	SetCollisionPair<TreeTrunk, Bullet>();

	SetCollisionPair<TreeTrunk, PlayerTank>();

	SetCollisionPair<PlayerTank, Powerup>();

	SetCollisionPair<PlayerTurret, Bullet>();

	SetCollisionPair<Player2Turret, Bullet>();

	SetCollisionPair<Player2Tank, Bullet>();

	SetCollisionPair<Player2Tank, Powerup>();

	SetCollisionPair<Ruins, Bullet>();

	SetCollisionPair<Ruins, PlayerTank>();

	SetCollisionPair<Ruins, EnemyTank>();

	SetCollisionPair<Rock, Bullet>();

	SetCollisionPair<Rock, PlayerTank>();

	SetCollisionPair<Rock, EnemyTank>();

	SetCollisionPair<EnemyFighter, Rock>();

	SetCollisionPair<EnemyFighter, TreeTrunk>();

	SetCollisionPair<EnemyFighter, Ruins>();

	SetCollisionPair<EnemyFighter, PlayerTank>();

	SetCollisionPair<EnemyFighter, Bullet>();

	SetCollisionTerrain<Bullet>();
}

void SceneTankBattle::IdentifyTerrainCells(Vect pos, float radius)
{
	pos;
	radius;
	//terrain->ShowCellRange(Vect(pos.X() - radius, 0, pos.Z() - radius), Vect(pos.X() + radius, 0, pos.Z() + radius));
}

void SceneTankBattle::DrawHUD()
{
	GameManager::GetEnemiesSS()->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera());
	GameManager::GetScoreSS()->Set("SCORE: " + std::to_string(GameManager::GetScore()));
	GameManager::GetScoreSS()->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera());
	int mins = int((TimeManager::GetTime() - timeStart) / 60);
	float secs = (TimeManager::GetTime() - timeStart) - 60 * mins;
	char buf[9];
	sprintf_s(buf, 9, "%02d:%05.2f", mins, secs);
	std::string str(buf, 8);
	GameManager::GetGameTimeSS()->Set(str);
	GameManager::GetGameTimeSS()->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera());
}

void SceneTankBattle::UpdateRemainingTanks()
{
	GameManager::GetEnemiesSS()->Set(std::to_string(remainingTanks) + " Tanks Remaining");
	if (remainingTanks <= 0)
	{
		SceneManager::SetNextScene(new SceneTankBattle());
	}
}


void SceneTankBattle::SceneEnd()
{

	delete player;
	delete player2;
	delete worldPlane;
	
	delete healPower;
	delete healPower2;
	delete healPower3;
	delete speedPower;
	delete speedPower2;
	delete damagePower;

	GameManager::Clear();
	
	BulletFactory::Terminate();
}