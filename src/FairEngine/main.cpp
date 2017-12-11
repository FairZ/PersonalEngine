#include "Engine.h"

int main(int argc, char* argv[])
{
	Engine::Initialise(argc, argv);

	Engine::Close();

	return 0;
}