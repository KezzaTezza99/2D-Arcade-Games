#include "Renderer.h"

void Renderer::Initialise()
{
	ClearBackBuffer();
}

void Renderer::CreateBuffers(HWND hwnd)
{
	RECT rect;

	GetClientRect(hwnd, &rect);
	m_bufferWidth = rect.right - rect.left;
	m_bufferHeight = rect.bottom - rect.top;

	int bufferSize = m_bufferWidth * m_bufferHeight * sizeof(u32);

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

void Renderer::ClearBackBuffer()
{
	u32* currentPixel = (u32*)m_bufferMemory;

	for (int y = 0; y < m_bufferHeight; y++)
	{
		for (int x = 0; x < m_bufferWidth; x++)
		{
			*currentPixel++ = 0xff00ff;
		}
	}
}

void Renderer::SetBackground(u32 colour)
{
	u32* currentPixel = (u32*)m_bufferMemory;

	for (int y = 0; y < m_bufferHeight; y++)
	{
		for (int x = 0; x < m_bufferWidth; x++)
		{
			*currentPixel++ = colour;
		}
	}
}

void Renderer::DrawRectInPixels(int x0, int y0, int x1, int y1, u32 colour)
{
	//Clamping the values to the min and max (buffer width / height)
	x0 = Clamp(0, m_bufferWidth, x0);
	x1 = Clamp(0, m_bufferWidth, x1);

	y0 = Clamp(0, m_bufferHeight, y0);
	y1 = Clamp(0, m_bufferHeight, y1);

	//For every pixel top to bottom and left to right
	for (int y = 0; y < y1; y++)
	{
		u32* pixel = (u32*)m_bufferMemory + x0 + y * m_bufferWidth;
		
		for (int x = x0; x < x1; x++)
		{
			//The current pixel is set to the desired colour
			*pixel++ = colour;
		}
	}
}

//The half sizes will be how width / height from the centre orgin of 0,0
void Renderer::DrawRect(float x, float y, float xHalfSize, float yHalfSize, u32 colour)
{
	float renderScale = 0.01f;

	x *= m_bufferHeight * renderScale;
	y *= m_bufferHeight * renderScale;
	xHalfSize *= m_bufferHeight * renderScale;
	yHalfSize *= m_bufferHeight * renderScale;

	x += m_bufferWidth / 2.0f;
	y += m_bufferWidth / 2.0f;

	//Changing into Pixels
	int x0 = x - xHalfSize;
	int x1 = x + xHalfSize;
	int y0 = y - yHalfSize;
	int y1 = y + yHalfSize;

	DrawRectInPixels(x0, y0, x1, y1, colour);
}

//Getters
void* Renderer::GetMemoryBuffer() { return m_bufferMemory; }
int Renderer::GetBufferHeight() { return m_bufferHeight; }
int Renderer::GetBufferWidth() { return m_bufferWidth; }
BITMAPINFO Renderer::GetBitmapBufferInfo() { return m_bufferBitmapInfo; }