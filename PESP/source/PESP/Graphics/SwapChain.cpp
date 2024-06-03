#include <PESP/Graphics/SwapChain.h>
#include <PESP/Graphics/RenderSystem.h>

SwapChain::SwapChain(HWND hwnd, ui32 width, ui32 height, RenderSystem* system) : m_system(system)
{
	ID3D11Device* device = m_system->m_d3d_device.Get();
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;//
	
	HRESULT hr = m_system->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);
	
	if (FAILED(hr))
		PESPError("SwapChain not Created successfully - SwapChain.cpp (ln24)");
	
	reloadBuffers(width, height);
}

void SwapChain::setFullScreen(bool fullscreen, ui32 width, ui32 height)
{
	resize(width, height);
	m_swap_chain->SetFullscreenState(fullscreen, nullptr);
}

void SwapChain::resize(ui32 width, ui32 height)
{
	m_rtv.Reset();
	m_dsv.Reset();

	m_swap_chain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	reloadBuffers(width, height);
}

bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);
	return true;
}

void SwapChain::reloadBuffers(ui32 width, ui32 height)
{
	ID3D11Device* device = m_system->m_d3d_device.Get();
	HRESULT hr;
	
	ID3D11Texture2D* buffer = NULL;
	
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	
	if (FAILED(hr))
		PESPError("SwapChain not Created successfully - SwapChain.cpp (ln60)");
	
	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (FAILED(hr))
		PESPError("SwapChain not Created successfully - SwapChain.cpp (ln66)");
	
	D3D11_TEXTURE2D_DESC tex_desc = {};
	tex_desc.Width = (width <= 0) ? 1 : width;
	tex_desc.Height = (height <= 0) ? 1 : height;
	tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex_desc.Usage = D3D11_USAGE_DEFAULT;
	tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex_desc.MipLevels = 1;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.MiscFlags = 0;
	tex_desc.ArraySize = 1;
	tex_desc.CPUAccessFlags = 0;

	device->CreateTexture2D(&tex_desc, nullptr, &buffer);

	if (FAILED(hr))
		PESPError("SwapChain not Created successfully -  SwapChain.cpp (ln84)");
	
	hr = device->CreateDepthStencilView(buffer, NULL, &m_dsv);
	
	buffer->Release();

	if (FAILED(hr))
		PESPError("SwapChain not Created successfully - SwapChain.cpp (ln93)");
}