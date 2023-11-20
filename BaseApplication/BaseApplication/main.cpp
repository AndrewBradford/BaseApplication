


#include "Application.h"


int main()
{



	Hollow::Application app;

	app.Init("Application", 1440, 960);

	app.Run();

	app.Cleanup();

}