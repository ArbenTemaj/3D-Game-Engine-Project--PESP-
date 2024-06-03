#pragma once
#include <PESP/Prerequisites.h>
#include <d3d11.h>
#include <wrl.h>

class VertexShader
{
public:
	VertexShader(const wchar_t* full_path, const char* entryPoint, RenderSystem* system);
private:
	Microsoft::WRL::ComPtr< ID3D11VertexShader> m_vs;
	RenderSystem* m_system = nullptr;
private:
	friend class RenderSystem;
	friend class DeviceContext;
};