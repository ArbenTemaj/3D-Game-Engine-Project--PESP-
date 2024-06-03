#include <PESP/Entity/TerrainComponent.h>
#include <PESP/Entity/Entity.h>
#include <PESP/Game/World.h>
#include <PESP/Game/Game.h>
#include <PESP/Graphics/GraphicsEngine.h>
#include <PESP/Graphics/RenderSystem.h>
#include <PESP/Graphics/ConstantBuffer.h>
#include <PESP/Math/VertexMesh.h>

TerrainComponent::TerrainComponent() = default;

TerrainComponent::~TerrainComponent()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
}

void TerrainComponent::setHeightMap(const TexturePtr& heightMap)
{
	m_heightMap = heightMap;
}

const TexturePtr& TerrainComponent::getHeightMap()
{
	return m_heightMap;
}

void TerrainComponent::setGroundMap(const TexturePtr& groundMap)
{
	m_groundMap = groundMap;
}

const TexturePtr& TerrainComponent::getGroundMap()
{
	return m_groundMap;
}

void TerrainComponent::setCliffMap(const TexturePtr& cliffMap)
{
	m_cliffMap = cliffMap;
}

const TexturePtr& TerrainComponent::getCliffMap()
{
	return m_cliffMap;
}

void TerrainComponent::setSize(const Vector3D& size)
{
	m_size = size;
}

Vector3D TerrainComponent::getSize()
{
	return m_size;
}

void TerrainComponent::generateTerrainMesh()
{
	const ui32 w = 512;//Width Terrain and amount of verties on the x
	const ui32 h = 512;//Height Terrain and amount of verties on the y

	const ui32 ww = w - 1; //number of quads on the x
	const ui32 hh = h - 1; //number of quads on the y


	VertexMesh* terrainMeshVertices = new VertexMesh[w * h];//Will hold the data for each vertex
	ui32* terrainMeshIndices = new ui32[ww * hh * 6];//Total Amount of indices

	auto i = 0;
	for (ui32 x = 0; x < w; x++)
	{
		for (ui32 y = 0; y < h; y++)
		{
			terrainMeshVertices[y * w + x] = {
				Vector3D((f32)x / (f32)ww, 0,(f32)y / (f32)hh),
				Vector2D((f32)x / (f32)ww, (f32)y / (f32)hh),
				Vector3D(),
				Vector3D(),
				Vector3D()
			};

			if (x < ww && y < hh) // if x and y are less than w - 1
			{
				terrainMeshIndices[i + 0] = (y + 1) * w + (x);
				terrainMeshIndices[i + 1] = (y)*w + (x);
				terrainMeshIndices[i + 2] = (y)*w + (x + 1);

				terrainMeshIndices[i + 3] = (y)*w + (x + 1);
				terrainMeshIndices[i + 4] = (y + 1) * w + (x + 1);
				terrainMeshIndices[i + 5] = (y + 1) * w + (x);
				i += 6;
			}
		}
	}
	auto renderSytem = m_entity->getWorld()->getGame()->getGraphicsEngine()->getRenderSystem();
	m_meshVb = renderSytem->createVertexBuffer(terrainMeshVertices, sizeof(VertexMesh), w * h);
	m_meshIb = renderSytem->createIndexBuffer(terrainMeshIndices, ww * hh * 6);

	m_vertexShader = renderSytem->createVertexShader(L"PESP/Assests/Shaders/Terrain.hlsl", "vsmain");
	m_pixelShader = renderSytem->createPixelShader(L"PESP/Assests/Shaders/Terrain.hlsl", "psmain");
}

void TerrainComponent::updateData(void* data, ui32 size)
{
	auto renderSystem = m_entity->getWorld()->getGame()->getGraphicsEngine()->getRenderSystem();

	if (!m_cb) m_cb = renderSystem->createConstantBuffer(data, size);
	else
		m_cb->update(renderSystem->getImmediateDeviceContext(), data);
}

void TerrainComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
	generateTerrainMesh();
}