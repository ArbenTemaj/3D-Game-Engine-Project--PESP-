#pragma once
#include <PESP/Resource/Resource.h>
#include <PESP/Prerequisites.h>
#include <vector>

class GraphicsEngine;
class Material : public Resource
{
public:
	Material(const wchar_t* path, ResourceManager* manager);
	Material(const MaterialPtr& material, ResourceManager* manager);

	void addTexture(const TexturePtr& texture);
	void removeTexture(ui32 index);
	void setData(void* data, ui32 size);

	void setCullMode(const CullMode& mode);
	const CullMode getCullMode();
private:
	VertexShaderPtr m_vertex_shader = nullptr;
	PixelShaderPtr m_pixel_shader = nullptr;
	ConstantBufferPtr m_constant_buffer = nullptr;
	std::vector<Texture2DPtr> m_vec_textures;
	CullMode m_cull_mode = CullMode::Back;
private:
	friend class GraphicsEngine;
};