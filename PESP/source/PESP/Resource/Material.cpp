#include <PESP/Resource/Material.h>
#include <PESP/Graphics/VertexShader.h>
#include <PESP/Graphics/PixelShader.h>
#include <PESP/Graphics/ConstantBuffer.h>
#include <PESP/Resource/ResourceManager.h>
#include <PESP/Game/Game.h>
#include <PESP/Graphics/GraphicsEngine.h>
#include <PESP/Graphics/RenderSystem.h>
#include <PESP/Resource/Texture.h>

Material::Material(const wchar_t* path, ResourceManager* manager) : Resource(path, manager)
{
	auto rsys = manager->getGame()->getGraphicsEngine()->getRenderSystem();

	m_vertex_shader = rsys->createVertexShader(path, "vsmain");
	if (!m_vertex_shader) 
		PESPError("Material not created successfully - Material.cpp (ln16)");

	m_pixel_shader = rsys->createPixelShader(path, "psmain");
	if (!m_pixel_shader) 
		PESPError("Material not created successfully - Material.cpp (ln20)");
}

Material::Material(const MaterialPtr& material, ResourceManager* manager) : Resource(L"", manager)
{
	m_vertex_shader = material->m_vertex_shader;
	m_pixel_shader = material->m_pixel_shader;
}

void Material::addTexture(const TexturePtr& texture)
{
	m_vec_textures.push_back(texture->m_texture);
}

void Material::removeTexture(ui32 index)
{
	if (index >= this->m_vec_textures.size()) return;
	m_vec_textures.erase(m_vec_textures.begin() + index);
}

void Material::setData(void* data, ui32 size)
{
	auto rsys = m_manager->getGame()->getGraphicsEngine()->getRenderSystem();
	if (!m_constant_buffer)
		m_constant_buffer = rsys->createConstantBuffer(data, size);
	else
		m_constant_buffer->update(rsys->getImmediateDeviceContext(), data);
}

void Material::setCullMode(const CullMode& mode)
{
	m_cull_mode = mode;
}

const CullMode Material::getCullMode()
{
	return m_cull_mode;
}