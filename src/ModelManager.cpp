#include "ModelManager.h"
#include <stdexcept>
#include "M_Assert.h"

ModelManager* ModelManager::ptrInstance = nullptr;

ModelManager::ModelManager()
{
	privLoad(Model::PreMadeModels::UnitBox_WF);
	privLoad(Model::PreMadeModels::UnitSphere);
	privLoad(Model::PreMadeModels::UnitSquareXY);
}

void ModelManager::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


ModelManager::~ModelManager()
{
	//delete all entities.
	for (std::map<std::string, Model*>::iterator it = myMap.begin(); it != myMap.end(); it++)
	{
		delete it->second;
	}
	for (std::map<Model::PreMadeModels, Model*>::iterator it = premade.begin(); it != premade.end(); it++)
	{
		delete it->second;
	}
}
Model* ModelManager::privGet(std::string key)
{
	// test for non existing key
	std::string errmsg = "Key \'" + key + "\' does not exists";
	M_Assert(myMap[key] != nullptr, errmsg.c_str());
	return myMap[key];
}

Model* ModelManager::privGetPremade(Model::PreMadeModels pm)
{
	return premade[pm];
}

void ModelManager::privLoad(std::string key, std::string path)
{
	//test for used key
	std::string errmsg = "Key \'" + key + "\' already exists";
	M_Assert(myMap[key] == nullptr, errmsg.c_str());
	myMap[key] = new Model((DefaultPath + path).c_str());
}
void ModelManager::privLoad(Model::PreMadeModels pm)
{
	//test for used key
	std::string errmsg = "Key \'" + std::to_string(int(pm)) + "\' already exists";
	M_Assert(premade[pm] == nullptr, errmsg.c_str());
	premade[pm] = new Model(pm);
}

void ModelManager::privLoad(std::string key, int planeSize, int uRep, int vRep)
{
	//test for used key
	std::string errmsg = "Key \'" + key + "\' already exists";
	M_Assert(myMap[key] == nullptr, errmsg.c_str());
	myMap[key] = new Model(planeSize, uRep, vRep);
}