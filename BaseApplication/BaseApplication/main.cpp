


#include "Application.h"


int main()
{




	Hollow::Application app;

	app.Init("Application", 800, 600);

	app.Run();

	app.Cleanup();

}