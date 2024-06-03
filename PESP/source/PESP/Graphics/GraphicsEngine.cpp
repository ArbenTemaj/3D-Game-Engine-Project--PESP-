//---------  Graphics  ---------//
#include <PESP/Graphics/GraphicsEngine.h>
#include <PESP/Graphics/RenderSystem.h>
#include <PESP/Graphics/DeviceContext.h>
#include <PESP/Graphics/IndexBuffer.h>
#include <PESP/Graphics/SwapChain.h>
#include <PESP/Graphics/Font2D.h>
//---------  Resources ---------//
#include <PESP/Resource/ResourceManager.h>
#include <PESP/Resource/Mesh.h>
#include <PESP/Resource/Texture.h>
#include <PESP/Resource/Material.h>
#include <PESP/Resource/Font.h>
//---------  Game  ---------//
#include <PESP/Game/Game.h>
#include <PESP/Game/Display.h>
//---------  Math  ---------//
#include <PESP/Math/Matrix4x4.h>
#include <PESP/Math/Vector4D.h>
#include <PESP/Prerequisites.h>
//---------  Entities Components  ---------//
#include <PESP/Entity/TransformComponent.h>
#include <PESP/Entity/MeshComponent.h>
#include <PESP/Entity/CameraComponent.h>
#include <PESP/Entity/LightComponent.h>
#include <PESP/Entity/TerrainComponent.h>
#include <PESP/Entity/WaterComponent.h>
#include <PESP/Entity/FogComponent.h>
#include <PESP/Entity/TextComponent.h>
#include <PESP/Entity/Entity.h>

__declspec(align(16))
struct CameratData
{
	Matrix4x4 view;
	Matrix4x4 proj;
	Vector4D position;
};

__declspec(align(16))
struct LightData
{
	Vector4D color;
	Vector4D direction;
};

__declspec(align(16))
struct TerrainData
{
	Vector4D size;
	f32 heightMapSize = 0.0f;
};

__declspec(align(16))
struct WaterData
{
	Vector4D size;
	f32 heightMapSize = 0.0f;
};

__declspec(align(16))
struct FogData
{
	Vector4D color;
	f32 start;
	f32 end;
	f32 enable;
};

__declspec(align(16))
struct ConstantData
{
	Matrix4x4 world;
	float time;
	CameratData camera;
	LightData light;
	TerrainData terrain;
	WaterData water;
	FogData fog;
};

GraphicsEngine::GraphicsEngine(Game* game) : m_game(game)
{
	m_render_system = std::make_unique<RenderSystem>();
}

void GraphicsEngine::update()
{
	auto swapChain = m_game->m_display->m_swapChain;
	auto context = m_render_system->getImmediateDeviceContext();
	m_render_system->clearState();

	ConstantData constData = {};
	constData.time = m_game->m_totalTime;


	Vector4D fogColor = Vector4D(0, 0, 0, 0);

	for (auto f : m_fogs)
	{
		constData.fog.enable = true;
		fogColor = f->getColor();
		constData.fog.color = fogColor;
		constData.fog.start = f->getStart();
		constData.fog.end = f->getEnd();
	}


	context->clearRenderTargetColor(swapChain, fogColor.x, fogColor.y, fogColor.z, 1);
	auto winSize = m_game->m_display->getClientSize();
	context->setViewportSize(winSize.width, winSize.height);



	for (auto c : m_cameras) // for all cameras
	{
		auto t = c->getEntity()->getTransform();
		constData.camera.position = t->getPosition();
		c->setScreenArea(winSize);
		c->getViewMatrix(constData.camera.view);
		c->getProjectionMatrix(constData.camera.proj);
	}


	for (auto l : m_lights) // for all lights
	{
		auto t = l->getEntity()->getTransform();
		Matrix4x4 w;
		t->getWorldMatrix(w);
		constData.light.direction = w.getZDirection();
		constData.light.color = l->getColor();
	}

	for (auto m : m_meshes) // for all meshes
	{
		auto transform = m->getEntity()->getTransform();
		transform->getWorldMatrix(constData.world);

		auto mesh = m->getMesh().get();
		const auto materials = m->getMaterials();


		context->setVertexBuffer(mesh->m_vertex_buffer);
		context->setIndexBuffer(mesh->m_index_buffer);


		for (auto i = 0; i < mesh->getNumMaterialSlots(); i++)
		{
			if (i >= materials.size()) break;
			auto mat = materials[i].get();

			m_render_system->setCullMode(mat->getCullMode());

			mat->setData(&constData, sizeof(ConstantData));
			context->setConstantBuffer(mat->m_constant_buffer);

			context->setVertexShader(mat->m_vertex_shader);
			context->setPixelShader(mat->m_pixel_shader);

			context->setTexture(&mat->m_vec_textures[0], (unsigned int)mat->m_vec_textures.size());

			auto slot = mesh->getMaterialSlot(i);
			context->drawIndexedTriangleList((unsigned int)slot.num_indices, (unsigned int)slot.start_index, 0);
		}
	}

	for (auto t : m_terrains) // for all terrains
	{
		auto transform = t->getEntity()->getTransform();
		transform->getWorldMatrix(constData.world);
		constData.terrain.size = t->getSize();
		constData.terrain.heightMapSize = t->getHeightMap()->getTexture()->getSize().width;

		context->setVertexBuffer(t->m_meshVb);
		context->setIndexBuffer(t->m_meshIb);

		m_render_system->setCullMode(CullMode::Back);
		t->updateData(&constData, sizeof(constData));
		context->setConstantBuffer(t->m_cb);

		context->setVertexShader(t->m_vertexShader);
		context->setPixelShader(t->m_pixelShader);

		Texture2DPtr terrainTexture[3];
		terrainTexture[0] = t->getHeightMap()->getTexture();
		terrainTexture[1] = t->getGroundMap()->getTexture();
		terrainTexture[2] = t->getCliffMap()->getTexture();

		context->setTexture(terrainTexture, 3);

		context->drawIndexedTriangleList((ui32)t->m_meshIb->getSizeIndexList(), 0, 0);
	}

	for (auto w : m_waterComps) // for all water
	{
		auto transform = w->getEntity()->getTransform();
		transform->getWorldMatrix(constData.world);
		constData.water.size = w->getSize();
		constData.water.heightMapSize = w->getWaveHeightMap()->getTexture()->getSize().width;

		context->setVertexBuffer(w->m_meshVb);
		context->setIndexBuffer(w->m_meshIb);

		m_render_system->setCullMode(CullMode::Back);
		w->updateData(&constData, sizeof(constData));
		context->setConstantBuffer(w->m_cb);

		context->setVertexShader(w->m_vertexShader);
		context->setPixelShader(w->m_pixelShader);

		Texture2DPtr waterTexture[1];
		waterTexture[0] = w->getWaveHeightMap()->getTexture();

		context->setTexture(waterTexture, 1);

		context->drawIndexedTriangleList((ui32)w->m_meshIb->getSizeIndexList(), 0, 0);
	}

	for (auto t : m_text)
	{
		auto transform = t->getEntity()->getTransform();
		auto pos = transform->getPosition();

		auto font = t->getFont()->getFont();

		font->m_batch->Begin();
		font->m_font->DrawString(font->m_batch.get(), t->getText(), DirectX::XMFLOAT2(pos.x, pos.y));
		font->m_batch->End();
	}

	swapChain->present(true);
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system.get();
}

void GraphicsEngine::addComponent(Component* component)
{
	if (auto c = dynamic_cast<MeshComponent*>(component))
		m_meshes.emplace(c);
	else if (auto c = dynamic_cast<CameraComponent*>(component))
	{
		if (!m_cameras.size()) m_cameras.emplace(c);
	}
	else if (auto c = dynamic_cast<LightComponent*>(component))
	{
		if (!m_lights.size()) m_lights.emplace(c);
	}
	else if (auto c = dynamic_cast<TerrainComponent*>(component))
	{
		if (!m_terrains.size()) m_terrains.emplace(c);
	}
	else if (auto c = dynamic_cast<WaterComponent*>(component))
	{
		if (!m_waterComps.size()) m_waterComps.emplace(c);
	}
	else if (auto c = dynamic_cast<FogComponent*>(component))
	{
		if (!m_fogs.size()) m_fogs.emplace(c);
	}
	else if (auto c = dynamic_cast<TextComponent*>(component))
	{
		m_text.emplace(c);
	}
}

void GraphicsEngine::removeComponent(Component* component)
{
	if (auto c = dynamic_cast<MeshComponent*>(component))
		m_meshes.erase(c);
	else if (auto c = dynamic_cast<CameraComponent*>(component))
		m_cameras.erase(c);
	else if (auto c = dynamic_cast<LightComponent*>(component))
		m_lights.erase(c);
	else if (auto c = dynamic_cast<TerrainComponent*>(component))
		m_terrains.erase(c);
	else if (auto c = dynamic_cast<WaterComponent*>(component))
		m_waterComps.erase(c);
	else if (auto c = dynamic_cast<FogComponent*>(component))
		m_fogs.erase(c);
	else if (auto c = dynamic_cast<TextComponent*>(component))
		m_text.erase(c);
}

GraphicsEngine::~GraphicsEngine() = default;