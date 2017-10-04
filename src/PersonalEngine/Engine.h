#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <memory> //consider moving to cpp to avoid include loops

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