#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <memory>

class Engine;
class Input;

struct Subsystems
{
	//subsystem instances ordered in terms of dependency

	std::weak_ptr<Engine> engineInstance;
	std::weak_ptr<Input> inputInstance;
};

class Engine
{
	friend class Input;

public:
	static void Initialise(int argc, char* argv[]);
	static void Close();
private:
	static std::shared_ptr<Subsystems> subsystems;
	static void Display();
	static void Update();
	static void Resize(int _width, int _height);
	
	static std::weak_ptr<Engine> m_instance;
};

#endif