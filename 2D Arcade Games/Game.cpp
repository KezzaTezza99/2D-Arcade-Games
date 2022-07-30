#include "Window.h"

Window* gameWindow = new Window();

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//Game Loop
	while (gameWindow->IsRunning())
	{
		//Input
		MSG message;

		//reading the messages to see if need to exit
		while (PeekMessage(&message, gameWindow->GetWindow(), 0, 0, PM_REMOVE))
		{
			//Handle Keyboard Input
			switch (message.message)
			{	
				default:
				{
					//Dispatch messages
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}
		}

		//Simulate
		unsigned int* currentPixel = (unsigned int*)gameWindow->GetMemoryBuffer();

		for (int y = 0; y < gameWindow->GetBufferHeight(); y++)
		{
			for (int x = 0; x < gameWindow->GetBufferWidth(); x++)
			{
				*currentPixel++ = 0xff5500;
				//9.30
			}
		}

		//Render
		BITMAPINFO data = gameWindow->GetBitmapBufferInfo();
		StretchDIBits(gameWindow->GetWindowContext(), 0, 0, gameWindow->GetBufferWidth(), gameWindow->GetBufferHeight(), 0, 0, gameWindow->GetBufferWidth(), gameWindow->GetBufferHeight(), gameWindow->GetMemoryBuffer(), &data, DIB_RGB_COLORS, SRCCOPY);
	}
}