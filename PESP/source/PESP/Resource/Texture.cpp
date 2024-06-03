#include <PESP/Resource/Texture.h>
#include <PESP/Resource/ResourceManager.h>
#include <PESP/Game/Game.h>
#include <PESP/Graphics/GraphicsEngine.h>
#include <PESP/Graphics/RenderSystem.h>

Texture::Texture(const wchar_t* full_path, ResourceManager* manager) : Resource(full_path, manager)
{
	m_texture = manager->getGame()->getGraphicsEngine()->getRenderSystem()->createTexture(full_path);
}

const Texture2DPtr& Texture::getTexture()
{
	return m_texture;
}