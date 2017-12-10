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
#include "Time.h"

//initialisation of static variables
std::shared_ptr<Scene> Engine::m_currentScene;
float Engine::fixedTime = 0.008f;
float Engine::updateTime = 0.016f;

void Engine::Initialise(int argc, char* argv[])
{	
	m_currentScene = std::make_shared<Scene>();

	//initialise glut 
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutSetOption(GLUT_MULTISAMPLE, 4);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutCreateWindow("Personal Engine");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutIgnoreKeyRepeat(1);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutFullScreenToggle();
	glutWarpPointer(Window::GetWidth() / 2, Window::GetHeight() / 2);

	//glut callback setting
	glutDisplayFunc(Display);
	glutIdleFunc(Update);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);
	glutPassiveMotionFunc(MouseMove);

	//initialise glew
	glewInit();

	//initialize gl values (probably move to renderer)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glViewport(0, 0, 800, 600);
	glEnable(GL_MULTISAMPLE);

	//initialise openal
	ALCdevice* device = alcOpenDevice(NULL);
	ALCcontext* context = alcCreateContext(device,NULL);
	alcMakeContextCurrent(context);

	//initialise scene
	m_currentScene->Init();
	//Load the specified scene
	m_currentScene->LoadScene();

	Time::m_lastTime = glutGet(GLUT_ELAPSED_TIME);

	//Begin GLUT main loop
	glutMainLoop();

}

void Engine::Close()
{
	//reset of scene will delete all smart pointers contained within to clear up any allocated memory
	m_currentScene.reset();

	ALCcontext* context = alcGetCurrentContext();
	ALCdevice* device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

std::weak_ptr<Scene> Engine::GetCurrentScene()
{
	return m_currentScene;
}

void Engine::Display()
{
	//resetting the mouse to the center during display prevents glutWarpPointer from calling MouseMotion
	glutWarpPointer(Window::GetWidth() / 2, Window::GetHeight() / 2);
	//run rendercontroller to render scene and apply postprocessing
	m_currentScene->Render();

	//show the rendered frame
	glutSwapBuffers();
}

void Engine::Update()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	Time::m_deltaTime += (currentTime - Time::m_lastTime) / 1000.0f;
	Time::m_fixedDeltaTime += (currentTime - Time::m_lastTime) / 1000.0f;
	Time::m_lastTime = currentTime;

	if (Time::m_fixedDeltaTime >= fixedTime)
	{
		m_currentScene->FixedUpdate();
		Time::m_fixedDeltaTime = 0.0f;
	}

	if (Time::m_deltaTime >= updateTime)
	{
		//Update all elements in scene
		m_currentScene->Update();

		//clear up and down keys once all input dependant code has been run
		Input::m_upKeys.clear();
		Input::m_upMouseButtons.clear();
		Input::m_downKeys.clear();
		Input::m_downMouseButtons.clear();
		Input::m_xDiff = 0;
		Input::m_yDiff = 0;		

		Time::m_deltaTime = 0;

		Camera::mainCamera.lock()->UpdateListener();
		//tell glut to run display function
		glutPostRedisplay();
	}
}

void Engine::Resize(int _width, int _height)
{
	Window::Resize(_width, _height);
	m_currentScene->Resize();
}

#pragma region Input Handling

void Engine::KeyDown(unsigned char _key, int _mouseX, int _mouseY)
{
	if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{
		if(_key > 64 && _key < 91)
		{
			_key += 32;
		}
	}
	//add activated key to the down vector and the active keys vector
	Input::m_downKeys.push_back(_key);
	Input::m_keys.push_back(_key);
	if (_key == 27)
	{
		glutFullScreenToggle();
		glutLeaveMainLoop();
	}
}

void Engine::KeyUp(unsigned char _key, int _mouseX, int _mouseY)
{
	if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{
		if(_key > 64 && _key < 91)
		{
			_key += 32;
		}
	}
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

void Engine::MouseMove(int _xMove, int _yMove)
{
	Input::m_xDiff = (Window::GetWidth() / 2) - _xMove;
	Input::m_yDiff = _yMove - (Window::GetHeight() / 2);
}

#pragma endregion