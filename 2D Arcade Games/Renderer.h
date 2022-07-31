#pragma once
#include <Windows.h>
#include "Utils.h"

class Renderer
{
private:
	//Buffer
	void* m_bufferMemory;
	int m_bufferHeight;
	int m_bufferWidth;
	BITMAPINFO m_bufferBitmapInfo;

public:
	void Initialise();
	void CreateBuffers(HWND hwnd);

	//Helper Methods
	void ClearBackground();
	void SetBackground(u32 colour);

	//TODO: Rename the x0 etc to top, bottom, right, left for clarity
	void DrawRectInPixels(int x0, int y0, int x1, int y1, u32 colour);
	void DrawRect(float x, float y, float xHalfSize, float yHalfSize, u32 colour);

	//Getters
	void* GetMemoryBuffer();
	int GetBufferHeight();
	int GetBufferWidth();
	BITMAPINFO GetBitmapBufferInfo();
};

