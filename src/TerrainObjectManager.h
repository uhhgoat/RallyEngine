#pragma once
#include <map>
#include <string>
class Terrain;

class TerrainObjectManager
{
private:
	friend class Rally;
	static TerrainObjectManager* ptrInstance;

	TerrainObjectManager();
	TerrainObjectManager(const TerrainObjectManager&) = delete;
	TerrainObjectManager& operator=(const TerrainObjectManager&) = delete;
	~TerrainObjectManager();

	const std::string DefaultPath = "Textures/";

	std::map<std::string, Terrain*> myMap;

	static TerrainObjectManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TerrainObjectManager;
		return *ptrInstance;
	};
	Terrain* privGet(std::string key);

	void privLoad(std::string key, std::string path, float len, float maxheight, float ytrans, std::string textureKey, int RepeatU, int RepeatV);


	static void Delete();
public:

	static Terrain* Get(std::string key) { return Instance().privGet(key); };

	static void Load(std::string key, std::string path, float len, float maxheight, float ytrans, std::string textureKey, int RepeatU, int RepeatV) { Instance().privLoad(key, path, len, maxheight, ytrans, textureKey, RepeatU, RepeatV); };

};
