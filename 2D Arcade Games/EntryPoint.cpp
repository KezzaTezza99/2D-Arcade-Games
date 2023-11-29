#include "Window.h"
#include "Input.h"

Window* gameWindow = new Window();

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//Input
	Input input;
	input.UserInputDevice(&input, gameWindow->GetRenderer());

	//Clearing BackBuffer
	gameWindow->GetRenderer()->ClearBackBuffer();
	gameWindow->GetRenderer()->SetBackground(0xffffff);

	//Game Loop
	while (gameWindow->IsRunning())
	{
		//Input
		MSG message;

		//Resetting Input
		input.ResetKeysPressed();
		
		Keys keys{};

		//reading the messages to see if need to exit
		while (PeekMessage(&message, gameWindow->GetWindow(), 0, 0, PM_REMOVE))
		{
			//Handle Keyboard Input
			switch (message.message)
			{	
				case WM_KEYUP:
				case WM_KEYDOWN:
				{
					u32 vk_code = (u32)message.wParam;

					switch (vk_code)
					{
						case 'W':
						{
							input.ProcessKeyPress(BUTTON_W, 'W', &message);
							break;
						}
						case 'S':
						{
							input.ProcessKeyPress(BUTTON_S, 'S', &message);
							break;
						}
					}
					break;
				}
				default:
				{
					//Dispatch messages
					TranslateMessage(&message);
				
					DispatchMessage(&message);
				}
			}
		}

		//Simulate Game

		//Rendering the buffer to the screen (do this last)
		//Render - Can't do this in Render as i'll have circular dependency (TODO: Fix this)
		BITMAPINFO data = gameWindow->GetRenderer()->GetBitmapBufferInfo();
		StretchDIBits(gameWindow->GetWindowContext(), 0, 0, gameWindow->GetRenderer()->GetBufferWidth(), gameWindow->GetRenderer()->GetBufferHeight(), 0, 0, 
			gameWindow->GetRenderer()->GetBufferWidth(), gameWindow->GetRenderer()->GetBufferHeight(), gameWindow->GetRenderer()->GetMemoryBuffer(), 
			&data, DIB_RGB_COLORS, SRCCOPY);
	}
}