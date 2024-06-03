#include  <PESP/Resource/ResourceManager.h>
#include  <PESP/Resource/Mesh.h>
#include  <PESP/Resource/Texture.h>
#include  <PESP/Resource/Material.h>
#include <PESP/Resource/Font.h>
#include <filesystem>

ResourceManager::ResourceManager(Game* game) : m_game(game)
{
}

ResourceManager::~ResourceManager() = default;

Game* ResourceManager::getGame()
{
	return m_game;
}

ResourcePtr ResourceManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	std::filesystem::path resourePath = file_path; 
	auto ext = resourePath.extension();

	auto it = m_map_resources.find(file_path);
	
	if (it != m_map_resources.end())
	{
		auto mat = std::dynamic_pointer_cast<Material>(it->second);
		if (mat) return std::make_shared<Material>(mat, this);
		return it->second;
	}

	if (!std::filesystem::exists(resourePath)) return ResourcePtr();//Checks if the file Path is real

	ResourcePtr resPtr;

	if (!ext.compare(L".obj"))
		resPtr = std::make_shared<Mesh>(resourePath.c_str(), this);
	else if (!ext.compare(L".jpg") || !ext.compare(L".png") || !ext.compare(L".bmp"))
		resPtr = std::make_shared<Texture>(resourePath.c_str(), this);
	else if (!ext.compare(L".hlsl") || !ext.compare(L".fx"))
		resPtr = std::make_shared<Material>(resourePath.c_str(), this);
	else if (!ext.compare(L".font"))
		resPtr = std::make_shared<Font>(resourePath.c_str(), this);

	if (resPtr)
	{
		m_map_resources.emplace(file_path, resPtr);
		return resPtr;
	}
	return nullptr;
}