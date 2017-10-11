#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Engine.h"
#include "Window.h"
#include "Input.h"

//initialisation of static variable
std::shared_ptr<Subsystems> Engine::subsystems;

void Engine::Initialise(int argc, char* argv[])
{
	//subsystem intialisation
	//THIS DOES ABSOLUTELY NOTHING ATM
	//it also probably doesn't want to be called subsystems, it's more of the like scene basically like it should have all of the stuff that is used in a scene like the gameobjects and textures and such
	if (!subsystems)
	{
		subsystems.reset(new Subsystems());
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
	glCullFace(GL_FRONT);

	//Begin GLUT main loop
	glutMainLoop();

}

void Engine::Close()
{
	//reset of subsystems will delete all smart pointers contained within effectively unloading the entire engine
	subsystems.reset();
}

void Engine::Display()
{
	//call renderer draw function in future
	if (Input::GetKey('a'))
	{
		glClearColor(255.0f / 255.0f, 0, 0, 1.0f);
	}
	else
	{
		glClearColor(0, 0, 0, 1.0f);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 800, 600);

	glutSwapBuffers();
}

void Engine::Update()
{
	//call scene graph update function in future

	//clear up and down keys and buttons at end of update
	Input::m_upKeys.clear();
	Input::m_upMouseButtons.clear();
	Input::m_downKeys.clear();
	Input::m_downMouseButtons.clear();

	//tell glut to run display function
	glutPostRedisplay();
}

void Engine::Resize(int _width, int _height)
{
	//call the window resize function
	Window::Resize(_width, _height);
}

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