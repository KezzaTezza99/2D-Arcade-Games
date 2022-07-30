#include <windows.h>

class Window
{
public:
	bool m_running;

public:
	HWND m_window;										//Window
	HDC m_context;										//Window Context
	
	//Buffers
	void* m_bufferMemory;
	int m_bufferHeight;
	int m_bufferWidth;
	BITMAPINFO m_bufferBitmapInfo;

public:
	Window();
	~Window();

	void Initialise();
	bool IsRunning();
	void SetRunning(bool isRunning);
	void CreateBuffers(HWND hwnd);
	//Virtual Methods?
	// 

	//Getters
	HWND GetWindow();
	HDC GetWindowContext();
	void* GetMemoryBuffer();
	int GetBufferHeight();
	int GetBufferWidth();
	BITMAPINFO GetBitmapBufferInfo();
};