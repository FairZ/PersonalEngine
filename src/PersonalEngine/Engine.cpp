#include "Engine.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <exception>

Engine* Engine::m_instance = nullptr;

void Engine::Initialise(int argc, char* argv[])
{
	//singleton assurance
	if (m_instance != nullptr)
	{
		throw std::exception();
		return;
	}
	m_instance = new Engine();

	//initialise glut 
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Personal Engine");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutDisplayFunc(Display);
	glutIdleFunc(Update);

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
	//add closing code here
}

void Engine::Display()
{
	//call renderer draw function in future
	glClearColor(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 800, 600);

	glutSwapBuffers();
}

void Engine::Update()
{
	//call scene graph update function in future
}
