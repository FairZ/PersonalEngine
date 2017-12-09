#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Entity.h"
#include "Scene.h"

/// \brief Class linking all other engine subsystems and containing the current game scene.
///
/// Privately contains GLUT callback functions and the currently loaded scene.
class Engine
{
	friend class Entity;
	friend class RenderController;
public:
	/// \brief Must be called within main to initialise the engine
	static void Initialise(int argc, char* argv[]);
	/// \brief Must be called at end of main to shut down the engine safely
	static void Close();

	static std::weak_ptr<Scene> GetCurrentScene();

private:
	static std::shared_ptr<Scene> m_currentScene;

	static float fixedTime;
	static float updateTime;

	static void Display();
	static void Update();
	static void Resize(int _width, int _height);
	static void KeyDown(unsigned char _key, int _mouseX, int _mouseY);
	static void KeyUp(unsigned char _key, int _mouseX, int _mouseY);
	static void MouseClick(int _button, int _state, int _x, int _y);
	static void MouseMove(int _xMove, int _yMove);
};

#endif