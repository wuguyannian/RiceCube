#include "ricepch.h"
#include "base.h"
#include "Application.h"
#include "event/event.h"

int main()
{
	auto app = new RiceCube::Application();
	app->run();
	return 0;
}