#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <memory> //consider moving to cpp to avoid include loops

class Window;

//TODO: figure out how you want to do other parts of the engine, should they be static, should they be singletons,
//if not how will they be accessed, if so how will they be set up (Maybe use a context like karsten)
class Engine
{
public:
	static void Initialise(int argc, char* argv[]);
	static void Close();
private:
	static void Display();
	static void Update();
	
	static std::weak_ptr<Engine> m_instance;
};

#endif