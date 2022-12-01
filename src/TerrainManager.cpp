#include "TerrainManager.h"
#include "Terrain.h"
TerrainManager::~TerrainManager()
{
	currentTerrain = nullptr;
}

void TerrainManager::SetCurrentTerrain(Terrain* ter)
{
	currentTerrain = ter;
}

Terrain* TerrainManager::GetCurrentTerrain()
{
	return currentTerrain;
}

void TerrainManager::DrawTerrain()
{
	if(currentTerrain != nullptr)
		currentTerrain->Draw();
}

