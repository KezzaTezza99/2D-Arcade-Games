#ifndef __INPUT_
#define __INPUT_
#include <windows.h>
#include "Utils.h"
#include "Renderer.h"

struct KeyState
{
	bool isDown;
	bool keyChanged;
};

enum Keys
{
	BUTTON_W,
	BUTTON_S,
	BUTTON_COUNT,
};

class Input
{
private:
	Input* m_currentKeyboard;
	KeyState m_keysPressed[BUTTON_COUNT];

	//TEMP
	Renderer* m_renderer;
public:
	//void UserInputDevice(Input* self);
	//temp
	void UserInputDevice(Input* self, Renderer* renderer);
	void ResetKeysPressed();
	void ProcessKeyPress(Keys keyPressed, u32 keyCode, MSG* msg);
};
#endif //!__INPUT_
