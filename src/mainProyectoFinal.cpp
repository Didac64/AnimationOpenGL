//Using SDL, SDL OpenGL, GLEW, standard IO, and strings
#define STB_IMAGE_IMPLEMENTATION
#include <SDL.h>
#include <glad/glad.h>

#include "shaders.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <../stb_image/include/stb_image/stb_image.h>

#include <iostream>
#include <fstream>

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
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
unsigned int ebo;
unsigned int texture;

glm::vec3 CubePos[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
// TO DO : Declare Shader variables

//unsigned int vertexShader;
//unsigned int FragmentShader;
//unsigned int FragmentShader2;
//unsigned int FragmentShader3;
//unsigned int shaderProgram;
//unsigned int shaderProgram2;
//unsigned int shaderProgram3;
Uint32 frameStart;
int lastframe = SDL_GetTicks();
int deltatime = frameStart - lastframe;
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
				myshaders.init("resources/shadelFV");


			}
		}
	}

	return success;
}

void initGL()
{
	glEnable(GL_DEPTH_TEST);




	// TO DO : Declare vertex data


	float vertices[] = {
		// Cara frontal
	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,

	// Cara trasera
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,  0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 0.5f, 0.0f,  1.0f, 1.0f,

	// Cara izquierda
	-0.5f, -0.5f, -0.5f,  0.2f, 0.4f, 0.6f,  0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.4f, 0.6f, 0.8f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.6f, 0.8f, 1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.8f, 1.0f, 0.2f,  0.0f, 1.0f,

	// Cara derecha
	 0.5f, -0.5f, -0.5f,  0.9f, 0.3f, 0.1f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.7f, 0.5f, 0.3f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.7f, 0.9f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.3f, 0.9f, 0.7f,  0.0f, 1.0f,

	 // Cara superior
	 -0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,  0.0f, 0.0f,
	  0.5f,  0.5f, -0.5f,  0.4f, 0.4f, 0.6f,  1.0f, 0.0f,
	  0.5f,  0.5f,  0.5f,  0.6f, 0.6f, 0.4f,  1.0f, 1.0f,
	 -0.5f,  0.5f,  0.5f,  0.8f, 0.8f, 0.2f,  0.0f, 1.0f,

	 // Cara inferior
	 -0.5f, -0.5f, -0.5f,  0.1f, 0.1f, 0.1f,  0.0f, 0.0f,
	  0.5f, -0.5f, -0.5f,  0.3f, 0.3f, 0.3f,  1.0f, 0.0f,
	  0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,  1.0f, 1.0f,
	 -0.5f, -0.5f,  0.5f,  0.7f, 0.7f, 0.7f,  0.0f, 1.0f

	};

	unsigned int indices[] = {
		0, 1, 2,  0, 2, 3,      // frontal
		4, 5, 6,  4, 6, 7,      // trasera
		8, 9,10,  8,10,11,      // izquierda
		12,13,14, 12,14,15,      // derecha
		16,17,18, 16,18,19,      // superior
		20,21,22, 20,22,23       // inferior
	};
	



	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//TEXTURE
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("resources/images.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
		{
			format = GL_RED;
		}
		else if (nrChannels == 3)
		{
			format = GL_RGB;
		}
		else if (nrChannels == 4)
		{
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	// or set it via the texture class
	myshaders.use();
	myshaders.setInt("texture1", texture);



}

void update()
{
	//No per frame update needed
}

void render()
{
	

	
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TO DO : Use Shader, Bind VAO and Paint
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	float timepo = deltatime / 70.0f;

	glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	float radius = 10.0f;
	float camX = 0.0f;
	float camZ = 6.0f;
	float camY = 0.0f;
	//myshaders.use();
	view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	myshaders.setMat4("view", view);


	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	myshaders.setMat4("projection", projection);

	myshaders.use();

	glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	
		// calculate the model matrix for each object and pass it to shader before drawing

		/*glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, CubePos[0]);
		float angle = 20.0f;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		myshaders.setMat4("model", model);*/

		for (unsigned int i = 0; i < sizeof(CubePos) / sizeof(CubePos[0]); i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, CubePos[i]);
			float angle = 20.0f * i + SDL_GetTicks() / 70.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			myshaders.setMat4("model", model);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}

		
	
		glBindVertexArray(0); //puede desactivar el vao aunque no el ebo si esta en uso

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
	glDeleteBuffers(1, &ebo);
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
		const float FRAME_DELAY = 1000 / 60; // 60 FPS -> 16.67ms per frame
		
		
		int frameTime;
		//While application is running
		while (!quit)
		{
			frameStart = SDL_GetTicks();

			int deltatime = frameStart - lastframe;
			lastframe = frameStart;
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

			
			if (FRAME_DELAY > deltatime)
			{
				SDL_Delay(FRAME_DELAY - deltatime);
				
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}	