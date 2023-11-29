#include "Input.h"

void Input::UserInputDevice(Input* self, Renderer* renderer)
{
	m_currentKeyboard = self;
	m_renderer = renderer;
}


void Input::ResetKeysPressed()
{
	for (int i = 0; i < BUTTON_COUNT; i++)
		m_currentKeyboard->m_keysPressed[i].keyChanged = false;
}

void Input::ProcessKeyPress(Keys keyPressed, u32 keyCode, MSG* msg)
{
	bool keyIsDown = ((msg->lParam & (1 << 31)) == 0);

	m_currentKeyboard->m_keysPressed[keyPressed].keyChanged = keyIsDown != m_currentKeyboard->m_keysPressed[keyPressed].isDown;
	m_currentKeyboard->m_keysPressed[keyPressed].isDown = keyIsDown;

	//Handle each key behaviour here
	switch (keyCode)
	{
		case 'W':
		{
			if (m_currentKeyboard->m_keysPressed[keyPressed].isDown)
				m_renderer->DrawRect(0, 0, 10, 10, 0xff00ff);
			break;
		}
		case 'S':
		{
			if (m_currentKeyboard->m_keysPressed[keyPressed].isDown)
				m_renderer->DrawRect(0, 0, 10, 10, 0x000000);
			break;
		}
	}
}
