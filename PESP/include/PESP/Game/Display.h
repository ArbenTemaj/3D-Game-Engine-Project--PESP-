#pragma once
#include <PESP/Prerequisites.h>
#include <PESP/Math/Rect.h>
#include <PESP/Window/Window.h>

class Display : public Window
{
public:
	Display(Game* game);
	~Display();
protected:
	virtual void onSize(const Rect& size);
private:
	SwapChainPtr m_swapChain;
	Game* m_game = nullptr;
private:
	friend class GraphicsEngine;
};