#pragma once
#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

class Input
{
public:
	static bool isKeyPressed(int keyCode);
	static bool isMouseButtonPressed(int button);
	static float getMouseX();
	static float getMouseY();
};

#endif // !INPUT_CLASS_H
