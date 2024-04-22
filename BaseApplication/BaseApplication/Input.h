#pragma once


namespace Hollow {

	// which directions are the player moving in
	struct Movement {
		bool Forward = false;
		bool Backward = false;
		bool Left = false;
		bool Right = false;
	};

	// class manages the state of all tracked inputs
	class Input
	{


	public:

		enum KEYS {W, S, A, D, ESC};


		bool isKeyPressed(KEYS k) 
		{
			bool t = keyStates[k];
			keyStates[k] = false;
			return t;
		};
		
		
		bool isKeyDown(KEYS k) 
		{
			return keyStates[k];
		};

		void setKeyDown(KEYS k)
		{
			keyStates[k] = true;
		}

		void setKeyUp(KEYS k)
		{
			keyStates[k] = false;
		}

		float mousex = 400;
		float mousey = 300;

		float lastmousex = 400;
		float lastmousey = 300;

		bool firstMouse = true;


		bool mouseCaptured = false;

	private:

		bool keyStates[5] = { false };


	};

}