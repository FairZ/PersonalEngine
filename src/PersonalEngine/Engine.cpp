#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Engine.h"
#include "Window.h"
#include "Input.h"
#include "Scene.h"
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"

//initialisation of static variable
std::shared_ptr<Scene> Engine::m_currentScene;

void Engine::Initialise(int argc, char* argv[])
{
	//scene intialisation
	if (!m_currentScene)
	{
		m_currentScene.reset(new Scene());
	}

	//initialise glut 
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Personal Engine");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutIgnoreKeyRepeat(1);

	//glut callback setting
	glutDisplayFunc(Display);
	glutIdleFunc(Update);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseFunc(MouseClick);

	//initialise glew
	glewInit();

	//initialize gl values (probably move to renderer)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	//Load the specified scene
	m_currentScene->LoadScene();

	//Begin GLUT main loop
	glutMainLoop();

}

void Engine::Close()
{
	//reset of scene will delete all smart pointers contained within to clear up any allocated memory
	m_currentScene.reset();
}

void Engine::Display()
{
	//render all elements in the current scene
	m_currentScene->Render();

	//show the rnedered frame
	glutSwapBuffers();
	//clear the back buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::Update()
{
	//Update all elements in scene
	m_currentScene->Update();

	//clear up and down keys once all input dependant code has been run
	Input::m_upKeys.clear();
	Input::m_upMouseButtons.clear();
	Input::m_downKeys.clear();
	Input::m_downMouseButtons.clear();

	//tell glut to run display function
	glutPostRedisplay();
}

void Engine::Resize(int _width, int _height)
{
	Window::Resize(_width, _height);
}

#pragma region Input Handling

void Engine::KeyDown(unsigned char _key, int _mouseX, int _mouseY)
{
	//add activated key to the down vector and the active keys vector
	Input::m_downKeys.push_back(_key);
	Input::m_keys.push_back(_key);
}

void Engine::KeyUp(unsigned char _key, int _mouseX, int _mouseY)
{
	//remove the released key from the active vector and add it to the release vector
	for (std::vector<unsigned char>::iterator i = Input::m_keys.begin(); i != Input::m_keys.end(); i++)
	{
		if ((*i) == _key)
		{
			Input::m_keys.erase(i);
			break;
		}
	}

	Input::m_upKeys.push_back(_key);

}

void Engine::MouseClick(int _button, int _state, int _x, int _y)
{
	//if statement to decide whether the registered click was a press or release
	if(_state == GLUT_DOWN)
	{
		//if a press occured add activated button to the down vector and the active buttons vector
		Input::m_downMouseButtons.push_back(_button);
		Input::m_mouseButtons.push_back(_button);
	}
	else
	{
		//otherwise remove the released button from the active vector and add it to the release vector
		for (std::vector<int>::iterator i = Input::m_mouseButtons.begin(); i != Input::m_mouseButtons.end(); i++)
		{
			if ((*i) == _button)
			{
				Input::m_mouseButtons.erase(i);
				break;
			}
		}

		Input::m_upMouseButtons.push_back(_button);
	}
}

#pragma endregion