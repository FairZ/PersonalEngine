#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Engine.h"
#include "Window.h"

std::shared_ptr<Subsystems> Engine::subsystems;

void Engine::Initialise(int argc, char* argv[])
{
	//singleton assurance
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

	//glut callback setting
	glutDisplayFunc(Display);
	glutIdleFunc(Update);
	glutReshapeFunc(Resize);

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
	glClearColor(255.0f / 255.0f, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 800, 600);

	glutSwapBuffers();
}

void Engine::Update()
{
	//call scene graph update function in future
}

void Engine::Resize(int _width, int _height)
{
	Window::Resize(_width, _height);
}
