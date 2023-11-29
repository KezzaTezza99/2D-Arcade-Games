#ifndef __RENDERER_
#define __RENDERER_
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

	//Bitmap Handler
	HBITMAP m_bitmap;

	//Window Handler - the image will be loaded into the window
	HWND m_window;

public:
	void Initialise();
	void CreateBuffers(HWND hwnd);

	//Helper Methods
	void ClearBackBuffer();
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
#endif //!__RENDERER_