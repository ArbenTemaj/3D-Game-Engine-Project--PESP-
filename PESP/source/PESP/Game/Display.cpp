#include <PESP/Game/Display.h>
#include <PESP/Game/Game.h>
#include <PESP/Graphics/GraphicsEngine.h>
#include <PESP/Graphics/RenderSystem.h>
#include <PESP/Graphics/SwapChain.h>

Display::Display(Game* game) : m_game(game)
{
	Rect size = getClientSize();
	m_swapChain = game->getGraphicsEngine()->getRenderSystem()->createSwapChain(static_cast<HWND>(m_hwnd), size.width, size.height);
}

Display::~Display() = default;

void Display::onSize(const Rect& size)
{
	m_swapChain->resize(size.width, size.height);
	m_game->onDisplaySize(size);
}