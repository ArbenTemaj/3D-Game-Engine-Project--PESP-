#pragma once
#include <PESP/Resource/Resource.h>
#include <PESP/Prerequisites.h>
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
	ResourceManager(Game* game);
	~ResourceManager();

	template<typename T>
	std::shared_ptr<T> createResourceFromFile(const wchar_t* file_path)
	{
		return std::dynamic_pointer_cast<T>(createResourceFromFileConcrete(file_path));
	}

	Game* getGame();
private:
	ResourcePtr createResourceFromFileConcrete(const wchar_t* file_path);
private:
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;
	Game* m_game = nullptr;
};