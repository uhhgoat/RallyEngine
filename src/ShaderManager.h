#pragma once
#include <map>
#include <string>
#include "ShaderObject.h"

class ShaderManager
{
private:
	friend class Rally;
	static ShaderManager* ptrInstance;

	ShaderManager() = default;
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;
	~ShaderManager();

	const std::string DefaultPath = "Shaders/";

	std::map<std::string, ShaderObject*> myMap;

	static ShaderManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ShaderManager;
		return *ptrInstance;
	};
	ShaderObject* privGet(std::string key);
	void privLoad(std::string key, std::string path);

	static void Delete();
public:

	static ShaderObject* Get(std::string key) { return Instance().privGet(key); };

	static void Load(std::string key, std::string path) { Instance().privLoad(key, path); };

};
