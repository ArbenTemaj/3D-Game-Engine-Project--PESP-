#include <PESP/Window/Window.h>
#include <Windows.h>
#include <exception>

LRESULT CALLBACK WndProc(HWND hwnd, ui32 msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			break;
		}
		case WM_SIZE:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (window) window->onSize(window->getClientSize());
			break;
		}
		case WM_SETFOCUS:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (window)	window->onFocus();
			break;
		}
		case WM_KILLFOCUS:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onKillFocus();
			break;
		}
		case WM_MOUSEWHEEL:
		{
			int wheelDelta = GET_WHEEL_DELTA_WPARAM(wparam);
			int linesToScroll = wheelDelta / WHEEL_DELTA;
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			break;
		}
		case WM_DESTROY:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onDestroy();
			//::PostQuitMessage(0);
			break;
		}
		case WM_CLOSE:
		{
			::PostQuitMessage(0);
			break;
		}
		default:
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return NULL;
}

Window::Window()
{
	
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"MyWindowClass";
	wc.lpfnWndProc = &WndProc;
	
	auto classId = ::RegisterClassEx(&wc);
	if (!classId) PESPError(L"Window not created successfully - Window.cpp (ln65)");

	RECT rc = { 0,0, m_size.width, m_size.height };
	AdjustWindowRect(&rc, WS_EX_OVERLAPPEDWINDOW, false);

	m_hwnd = ::CreateWindowEx
	(
		NULL, MAKEINTATOM(classId),
		L"PESP1 | PESP Game",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, NULL, this
	);

	if (!m_hwnd) PESPError("Failed to create window - Window.cpp (ln80)");

	auto hwnd = static_cast<HWND>(m_hwnd);

	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}

//bool Window::broadcast()
//{
//	///Declarring/Creating a Varible Whcih Will hold the Messages from the Window
//	MSG msg;//MSG is short for message.
//		
//	if(!this->m_is_init)
//	{
//		/// .. and then stored for later lookup
//		SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
//		this->onCreate();
//		this->m_is_init = true;
//	}
//
//	
//	///A message loop that continuously retrieves messages from the application's message queue
//	if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
//	{
//		///Translates the Message for the next function to be able to read the Message
//		TranslateMessage(&msg);
//		//Runs some even lower level code in the backround to Help get the Message in the Parameters of the WnProc Function
//		//Based on the Message this Could be used the trgger certian Window Events in the WnProc's Switch cases.
//		DispatchMessage(&msg);
//	}
//
//	this->onUpdate();
//	///Gives the Computer a 1 Milli-second to realeve some streess on the CPU a bit before conutinuing
//	Sleep(1);
//
//	return true;
//}
//
//
//
////Return 1/True if the window is Running; If not it return 0/false 
//bool Window::isRun()
//{
//
//	if (m_is_run) broadcast();
//	return m_is_run;
//}

Rect Window::getClientSize()
{
	RECT rc = {};
	auto hwnd = static_cast<HWND>(m_hwnd);
	::GetClientRect(hwnd, &rc);
	::ClientToScreen(hwnd, (LPPOINT)&rc.left);
	::ClientToScreen(hwnd, (LPPOINT)&rc.right);
	return { rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top };
}

Rect Window::getScreenSize()
{
	RECT rc = {};
	rc.right = ::GetSystemMetrics(SM_CXSCREEN);
	rc.bottom = ::GetSystemMetrics(SM_CYSCREEN);
	return { 0, 0, rc.right - rc.left, rc.bottom - rc.top };
}

void Window::onCreate(){}

void Window::onUpdate(){}

void Window::onDestroy(){}

void Window::onFocus(){}

void Window::onKillFocus(){}

void Window::onSize(const Rect& size){}

Window::~Window()
{
	DestroyWindow(static_cast<HWND>(m_hwnd));
}