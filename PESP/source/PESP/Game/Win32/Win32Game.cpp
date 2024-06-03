#include <PESP/Game/Game.h>
#include <PESP/Window/Window.h>
#include <Windows.h>

void Game::run()
{
	onCreate();
	MSG msg = {};

	while (m_isRunning)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				m_isRunning = false;
				continue;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		onInternalUpdate();
	}
	onQuit();
}