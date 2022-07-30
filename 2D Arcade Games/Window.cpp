#include "Window.h"

Window* window;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//0 is success
	//-1 is to set running to false
	LRESULT result = 0;
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			window->SetRunning(false);
			break;
		}
		case WM_DESTROY:
		{
			window->SetRunning(false);
			break;
		}
		case WM_SIZE:
		{
			window->CreateBuffers(hwnd);
			break;
		}
		default:
		{
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return result;
}

//MOVE THIS
void Window::CreateBuffers(HWND hwnd)
{
	RECT rect;
	GetClientRect(hwnd, &rect);
	m_bufferWidth = rect.right - rect.left;
	m_bufferHeight = rect.bottom - rect.top;

	int bufferSize = m_bufferWidth * m_bufferHeight * sizeof(unsigned int);

	//Need memory of the heap
	if (m_bufferMemory)
		VirtualFree(m_bufferMemory, 0, MEM_RELEASE);
	m_bufferMemory = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	m_bufferBitmapInfo.bmiHeader.biSize = sizeof(m_bufferBitmapInfo.bmiHeader);
	m_bufferBitmapInfo.bmiHeader.biWidth = m_bufferWidth;
	m_bufferBitmapInfo.bmiHeader.biHeight = m_bufferHeight;
	m_bufferBitmapInfo.bmiHeader.biPlanes = 1;
	m_bufferBitmapInfo.bmiHeader.biBitCount = 32;
	m_bufferBitmapInfo.bmiHeader.biCompression = BI_RGB;
}


Window::Window()
{
	window = this;
	m_running = true;
	Initialise();
}

Window::~Window() { m_running = false; }

bool Window::IsRunning() { return m_running; }

void Window::SetRunning(bool isRunning) { m_running = isRunning; }

void Window::Initialise()
{
	//Create Window Class
	WNDCLASS windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = L"Game Window";
	windowClass.lpfnWndProc = window_callback;

	//Register Class
	RegisterClass(&windowClass);

	//Create Window
	m_window = CreateWindow(windowClass.lpszClassName, L"Arcade Game", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,
		CW_USEDEFAULT, 1280, 720, 0, 0, 0, 0);

	//Creating a Context
	m_context = GetDC(m_window);
}

HWND Window::GetWindow() { return m_window; }
HDC Window::GetWindowContext() { return m_context; }
void* Window::GetMemoryBuffer() { return m_bufferMemory; }
int Window::GetBufferHeight() { return m_bufferHeight; }
int Window::GetBufferWidth() { return m_bufferWidth; }
BITMAPINFO Window::GetBitmapBufferInfo() { return m_bufferBitmapInfo; }
