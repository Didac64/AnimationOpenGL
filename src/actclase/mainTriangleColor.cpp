//Using SDL, SDL OpenGL, GLEW, standard IO, and strings
/*
#include <SDL.h>
#include <glad/glad.h>


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

//color
float RGBA[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

// TO DO : Declare IDs for a VAO and a VBO


unsigned int vbo;
unsigned int vao;

// TO DO : Declare Shader variables

unsigned int vertexShader;
unsigned int FragmentShader;
unsigned int FragmentShader2;
unsigned int FragmentShader3;
unsigned int shaderProgram;
unsigned int shaderProgram2;
unsigned int shaderProgram3;

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

			}
		}
	}

	return success;
}

void initGL()
{
	// TO DO : Declare shaders code (Vertex and Fragment) use char* or strings
	const char* vertexShaderSoruce;
	vertexShaderSoruce = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSoruce;
	fragmentShaderSoruce = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n\0";
	const char* fragmentShaderSoruce2;
	fragmentShaderSoruce2 = "#version 330 core\n"
		"out vec4 FragColor2;\n"
		"void main()\n"
		"{\n"
		"   FragColor2 = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\n\0";
	const char* fragmentShaderSoruce3;
	fragmentShaderSoruce3 = "#version 330 core\n"
		"out vec4 FragColor3;\n"
		"void main()\n"
		"{\n"
		"   FragColor3 = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
		"}\n\0";

	// TO DO : Declare vertex data



	float vertices[] = {
//    x		y	  z
	-0.2f, 0.4f, 0.0f, //left izquierda
	0.2f, 0.4f, 0.0f, //right derecha
	0.0f, 0.8f, 0.0f,  //top
	-0.4f, 0.0f, 0.0f,
	-0.0f, 0.0f, 0.0f,
	-0.2f, 0.4f, 0.0f,
	0.4f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.2f, 0.4f, 0.0f
	};

	// TO DO : Initialize clear color

	glClearColor(RGBA[0], RGBA[1], RGBA[2], RGBA[3]);

	// TO DO : Create Vertex Shader, compile and check for errors

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSoruce, NULL);
	glCompileShader(vertexShader);

	//error?
	
	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, InfoLog);
		std::cout << "ERROR::SHADER::VERTEX::FAILED\n" << InfoLog << std::endl;
	}

	// TO DO : Create Fragment Shader, compile and check for errors
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fragmentShaderSoruce, NULL);
	glCompileShader(FragmentShader);

	FragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader2, 1, &fragmentShaderSoruce2, NULL);
	glCompileShader(FragmentShader2);

	FragmentShader3 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader3, 1, &fragmentShaderSoruce3, NULL);
	glCompileShader(FragmentShader3);

	//error?
	
	
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, InfoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::FAILED\n" << InfoLog << std::endl;
	}

	glGetShaderiv(FragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragmentShader2, 512, NULL, InfoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::FAILED\n" << InfoLog << std::endl;
	}

	glGetShaderiv(FragmentShader3, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragmentShader3, 512, NULL, InfoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::FAILED\n" << InfoLog << std::endl;
	}
	// TO DO : Link Shaders on a Shader Program and check for errors
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, FragmentShader);
	glLinkProgram(shaderProgram);

	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, InfoLog);
		std::cout << "ERROR::SHADER::PROGRAM::FAILED\n" << InfoLog << std::endl;
	}

	shaderProgram2 = glCreateProgram();

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, FragmentShader2);
	glLinkProgram(shaderProgram2);

	glGetShaderiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram2, 512, NULL, InfoLog);
		std::cout << "ERROR::SHADER::PROGRAM::FAILED\n" << InfoLog << std::endl;
	}

	shaderProgram3 = glCreateProgram();

	glAttachShader(shaderProgram3, vertexShader);
	glAttachShader(shaderProgram3, FragmentShader3);
	glLinkProgram(shaderProgram3);

	glGetShaderiv(shaderProgram3, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram3, 512, NULL, InfoLog);
		std::cout << "ERROR::SHADER::PROGRAM::FAILED\n" << InfoLog << std::endl;
	}
	// TO DO : Delete Shader objects (fragment and Vertex).
	glDeleteShader(vertexShader);
	glDeleteShader(FragmentShader);
	
	
	// TO DO : Generate VAO and inside it VBO. Enable Attribute and UnBind VAO after process
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

}

void update()
{
	//No per frame update needed
}

void render()
{
	//TO DO : Clear color buffer
	
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// TO DO : Use Shader, Bind VAO and Paint
	glUseProgram(shaderProgram);
	glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(shaderProgram2);
	//glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 3, 3);
	glUseProgram(shaderProgram3);
	//glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 6, 3);
	// TO DO : UnBind VAO and Shader Program

}

void close()
{
	//TO DO : Clear data in GPU
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shaderProgram);
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
}*/