#include <PESP/Graphics/PixelShader.h>
#include <PESP/Graphics/RenderSystem.h>
#include <PESP/Graphics/ShaderInclude.h>
#include <d3dcompiler.h>

PixelShader::PixelShader(const wchar_t* full_path, const char* entryPoint, RenderSystem* system) : m_system(system)
{
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;	

	ShaderInclude shaderInclude(full_path);

	D3DCompileFromFile(full_path, nullptr, &shaderInclude, entryPoint, "ps_5_0", 0, 0, &blob, &errorBlob);

	if (errorBlob)
		PESPWarning("Pixel Shader " << full_path << " compiled with errors: \n" << (char*)errorBlob->GetBufferPointer());
	if (!blob)
		PESPError("Pixel Shader " << full_path << " not created successfully.PixelShader.cpp (ln14)");
	if (FAILED(m_system->m_d3d_device.Get()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &m_ps)))
		PESPError("Pixel Shader " << full_path << " not created successfully. - PixelShader.cpp (ln16)");
}