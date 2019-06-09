#include "ricepch.h"
#include "application.h"
#include "log.h"

int main()
{
    RiceCube::Log::init();
	auto app = new RiceCube::Application();
	app->run();
	return 0;
}