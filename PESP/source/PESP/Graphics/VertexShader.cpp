#include <PESP/Graphics/VertexShader.h>
#include <PESP/Graphics/RenderSystem.h>
#include <PESP/Graphics/ShaderInclude.h>
#include <d3dcompiler.h>

VertexShader::VertexShader(const wchar_t* full_path, const char* entryPoint, RenderSystem* system) : m_system(system)
{
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

	ShaderInclude shaderInclude(full_path);

	D3DCompileFromFile(full_path, nullptr, &shaderInclude, entryPoint, "vs_5_0", 0, 0, &blob, &errorBlob);

	if (errorBlob)
		PESPWarning("Vertex Shader " << full_path << " compiled with errors: \n" << (char*)errorBlob->GetBufferPointer());
	if (!blob)
		PESPError("Vertex Shader " << full_path << " not created successfully. - VertexShader.cpp (ln14)");
	if (FAILED(m_system->m_d3d_device.Get()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &m_vs)))
		PESPError("Vertex Shader " << full_path << " not created successfully. - VertexShader.cpp (ln16)");
}