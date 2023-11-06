#pragma once



namespace Hollow {

	class Renderer;
	class Input;

	class StateBase
	{



		void frame(float dt, Input* input);

		void render(Hollow::Renderer* r);


	};

}
