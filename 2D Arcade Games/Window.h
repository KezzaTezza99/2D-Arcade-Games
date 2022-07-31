#pragma once
#include <windows.h>
#include "Renderer.h"

class Window
{
public:
	bool m_running;

public:
	HWND m_window;										//Window
	HDC m_context;										//Window Context
	Renderer* m_renderer;

public:
	Window();
	~Window();

	void Initialise();
	bool IsRunning();
	void SetRunning(bool isRunning);

	//Getters
	HWND GetWindow();
	HDC GetWindowContext();
	Renderer* GetRenderer() { return m_renderer; }
};