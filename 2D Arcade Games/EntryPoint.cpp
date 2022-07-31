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

		//Simulate Game
		gameWindow->GetRenderer()->SetBackground(0x000000);

		//Drawing the Playing Arena
		gameWindow->GetRenderer()->DrawRect(0, 0, 85, 45, 0xffffff);

		//Rendering the buffer to the screen (do this last)
		//Render - Can't do this in Render as i'll have circular dependency (TODO: Fix this)
		BITMAPINFO data = gameWindow->GetRenderer()->GetBitmapBufferInfo();
		StretchDIBits(gameWindow->GetWindowContext(), 0, 0, gameWindow->GetRenderer()->GetBufferWidth(), gameWindow->GetRenderer()->GetBufferHeight(), 0, 0, 
			gameWindow->GetRenderer()->GetBufferWidth(), gameWindow->GetRenderer()->GetBufferHeight(), gameWindow->GetRenderer()->GetMemoryBuffer(), 
			&data, DIB_RGB_COLORS, SRCCOPY);
	}
}