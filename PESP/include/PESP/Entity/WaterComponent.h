#pragma once
#include <PESP/Prerequisites.h>
#include <PESP/Entity/Component.h>
#include <PESP/Math/Vector3D.h>

class WaterComponent : public Component
{
public:
	WaterComponent();
	virtual ~WaterComponent();

	void setWaveHeightMap(const TexturePtr& heightMap);
	const TexturePtr& getWaveHeightMap();

	void setSize(const Vector3D& size);
	Vector3D getSize();
private:
	void generateWaterMesh();
	void updateData(void* data, ui32 size);
protected:
	virtual void onCreateInternal();
private:
	TexturePtr m_waterHeightMap;
	Vector3D m_size = Vector3D(2048, 8, 2048);//Size of the Sea

	VertexBufferPtr m_meshVb;
	IndexBufferPtr m_meshIb;
	ConstantBufferPtr m_cb;

	VertexShaderPtr m_vertexShader;
	PixelShaderPtr m_pixelShader;
private:
	friend class GraphicsEngine;
};