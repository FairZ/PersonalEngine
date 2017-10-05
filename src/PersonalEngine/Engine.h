#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <memory>

class Engine;
class Input;

struct Subsystems
{
	//subsystem instances ordered in terms of dependency

	//PRETTY SURE THIS DOES ABSOLUTELY NOTHING ATM
	std::weak_ptr<Engine> engineInstance;
	std::weak_ptr<Input> inputInstance;
};

class Engine
{
public:
	static void Initialise(int argc, char* argv[]);
	static void Close();
private:
	static std::shared_ptr<Subsystems> subsystems;
	static void Display();
	static void Update();
	static void Resize(int _width, int _height);
	static void KeyDown(unsigned char _key, int _mouseX, int _mouseY);
	static void KeyUp(unsigned char _key, int _mouseX, int _mouseY);
	static void MouseClick(int _button, int _state, int _x, int _y);

	
	static std::weak_ptr<Engine> m_instance;
};

#endif