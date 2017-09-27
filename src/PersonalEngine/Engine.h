#ifndef _ENGINE_H_
#define _ENGINE_H_

class Engine
{
public:
	static void Initialise(int argc, char* argv[]);
	static void Close();
	static void Begin();
private:
	static void Display();
	static void Update();
	static Engine* m_instance;
};

#endif