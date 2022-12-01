#pragma once
class Terrain;
class TerrainManager
{
private:
	Terrain* currentTerrain;

public:

	TerrainManager() = default;
	~TerrainManager();
	TerrainManager(const TerrainManager&) = delete;
	TerrainManager& operator=(const TerrainManager&) = delete;

	void SetCurrentTerrain(Terrain* ter);
	Terrain* GetCurrentTerrain();
	void DrawTerrain();

};