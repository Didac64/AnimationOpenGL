//Using SDL, SDL OpenGL, GLEW, standard IO, and strings

#include <SDL.h>
#include <glad/glad.h>
#include "shaders.h"

#include <iostream>
#include <fstream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int success;
char InfoLog[512];
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
SDL_GLContext gContext;

//set shaders
shaders myshaders;
//color

//float RGBA[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
//glClearColor(RGBA[0], RGBA[1], RGBA[2], RGBA[3]);
// TO DO : Declare IDs for a VAO and a VBO


unsigned int vbo;
unsigned int vao;

// TO DO : Declare Shader variables

//unsigned int vertexShader;
//unsigned int FragmentShader;
//unsigned int FragmentShader2;
//unsigned int FragmentShader3;
//unsigned int shaderProgram;
//unsigned int shaderProgram2;
//unsigned int shaderProgram3;

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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
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
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				std::cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				// glad: load all OpenGL function pointers
				// ---------------------------------------
				if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
				{
					std::cout << "Failed to initialize GLAD" << std::endl;
					success = false;
				}

				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					std::cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
				}

				initGL();
				myshaders.init("resources/shadersFV");
				

			}
		}
	}

	return success;
}

void initGL()
{





	// TO DO : Declare vertex data



	float vertices[] = {
		//			pos				color
		//    x		y	  z
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  //left izquierda
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //right derecha
			-0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  //top
			//-0.4f, 0.0f, 0.0f,
			//-0.0f, 0.0f, 0.0f,
			//-0.2f, 0.4f, 0.0f,
			//0.4f, 0.0f, 0.0f,
			//0.0f, 0.0f, 0.0f,
			//0.2f, 0.4f, 0.0f
	};

	


	
	
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
}

void update()
{
	//No per frame update needed
}

void render()
{
	

	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// TO DO : Use Shader, Bind VAO and Paint
	myshaders.use();
	glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	//glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	//glDrawArrays(GL_TRIANGLES, 3, 3);
	
	//glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	//glDrawArrays(GL_TRIANGLES, 6, 3);
	// TO DO : UnBind VAO and Shader Program

}

void close()
{
	//TO DO : Clear data in GPU
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	
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
			SDL_GL_SwapWindow(gWindow);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}