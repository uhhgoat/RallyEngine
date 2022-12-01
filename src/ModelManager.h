#pragma once
#include <map>
#include <string>
#include "Model.h"

class ModelManager
{
private:
	friend class Rally;
	static ModelManager* ptrInstance;

	ModelManager();
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;
	~ModelManager();

	const std::string DefaultPath = "Models/";

	std::map<std::string, Model*> myMap;
	std::map<Model::PreMadeModels, Model*> premade;

	static ModelManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ModelManager;
		return *ptrInstance;
	};
	Model* privGet(std::string key);
	Model* privGetPremade(Model::PreMadeModels pm);
	void privLoad(std::string key, std::string path);
	void privLoad(Model::PreMadeModels pm);
	//void privLoad(std::string key, std::string path, int uRep, int vRep);
	void privLoad(std::string key, int planeSize, int uRep, int vRep);

	static void Delete();
public:

	static Model* Get(std::string key) { return Instance().privGet(key); };
	static Model* GetPremadeModel(Model::PreMadeModels pm) { return Instance().privGetPremade(pm); };

	static void Load(std::string key, std::string path) { Instance().privLoad(key, path); };
	//static void Load(std::string key, Model::PreMadeModels pm) { Instance().privLoad(key, pm); };
	//static void Load(std::string key, std::string path, int uRep, int vRep) { Instance().privLoad(key, path, uRep, vRep); };
	static void Load(std::string key, int planeSize, int uRep, int vRep) { Instance().privLoad(key, planeSize, uRep, vRep); };

};
