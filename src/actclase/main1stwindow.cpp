
/*
//Using SDL, SDL OpenGL, GLAD, standard IO, and strings
#include <SDL.h>
// TO DO:  Add glad library
#include <glad/glad.h>

#include <string>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


//var RGBA
float rojo[4] = {1.0f, 0.0f, 0.0f, 1.0f};
bool a = false;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes rendering program and clear color
void initGL();

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
// TO DO: Declare SDL var for context
SDL_GLContext context = nullptr;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Create context
			// TO DO: Create context with SDL and verify if context has been created
			context = SDL_GL_CreateContext(gWindow);
			if (!context)
			{
				std::cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				//// TO DO: Initialize GLAD
				if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
				{
					std::cout << "failed to initilize GLAD" << std::endl;
					success = false;
				}
				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					std::cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
				}

				initGL();
			}
		}
	}

	return success;
}

void initGL()
{
	// TO DO : Initialize clear color in RED
	glClearColor(rojo[0], rojo[1], rojo[2], rojo[3]);
	
}

void update()
{
	//No per frame update needed
}

void render()
{
	// TO DO: Clear buffer with a color defined in initGL function like an alarm.
	
	
	if (a == false)
	{
		rojo[0] -= 0.1f;
		if (rojo[0] <= 0.0f)
		{
			a = true;
		}
	}
	else {
		rojo[0] += 0.1f;
		if (rojo[0] >= 1.0f)
		{
			a = false;
		}
	}
	
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(rojo[0], rojo[1], rojo[2], rojo[3]);
}

void close()
{
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		std::cout << "Failed to initialize!" << std::endl;
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_KEYDOWN) {
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						quit = true;
					}
				}
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			//Render quad
			render();

			//Update screen
			// TO DO: Add SDL command to update OpenGL Window
			SDL_GL_SwapWindow(gWindow);
			SDL_Delay(70);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

*/