#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <memory>
#include <string>
#include "Entity.h"

class Scene
{
	//scene stuff

	//THIS DOES NOTHING AT THE MOMENT
};

/// \brief Class linking all other engine subsystems and containing the current game scene.
///
/// Privately contains GLUT callback functions and the currently loaded scene.
class Engine
{
	friend class Entity;
public:
	/// \brief Must be called within main to initialise the engine
	static void Initialise(int argc, char* argv[]);
	/// \brief Must be called at end of user program to shut down the engine safely
	static void Close();
	/// \brief attempts to load the specified scene.
	/// \return false or true depending on failure or success respectively
	static bool LoadScene(std::string _filePath);
private:
	/// \brief The currently loaded scene
	static std::shared_ptr<Scene> m_currentScene;

	static void Display();
	static void Update();
	static void Resize(int _width, int _height);
	static void KeyDown(unsigned char _key, int _mouseX, int _mouseY);
	static void KeyUp(unsigned char _key, int _mouseX, int _mouseY);
	static void MouseClick(int _button, int _state, int _x, int _y);
};

#endif