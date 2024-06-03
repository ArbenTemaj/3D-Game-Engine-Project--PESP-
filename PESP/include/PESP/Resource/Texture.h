#pragma once
#include <PESP/Resource/Resource.h>
#include <PESP/Prerequisites.h>

class Texture : public Resource
{
public:
	Texture(const wchar_t* full_path, ResourceManager* manager);
	const Texture2DPtr& getTexture();
private:
	Texture2DPtr m_texture;
private:
	friend class Material;
};