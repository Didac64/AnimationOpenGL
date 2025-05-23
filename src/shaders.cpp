#include "shaders.h"

using namespace std;

shaders::shaders()
{
	
}

shaders::~shaders()
{
}



void shaders::init(const GLchar* filename)
{
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;
	string vertexsoruce;
	string fragmentsoruce;

	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	

	// vertex--
	vertexsoruce.append(filename);
	vertexsoruce.append(".vert");
	

	vShaderFile.open(vertexsoruce, ios::in);
	if (!vShaderFile.is_open())
	{
		cout << "[ERROR] no se pudo abrir el archivo" << endl;
	}
	while (!vShaderFile.eof())
	{
		string apoyoV;
		getline(vShaderFile, apoyoV);
		vertexCode.append(apoyoV + "\n");
	}
	vShaderFile.close();
	
	// fragment--
	fragmentsoruce.append(filename);
	fragmentsoruce.append(".frag");

	fShaderFile.open(fragmentsoruce, ios::in);
	if (!fShaderFile.is_open())
	{
		cout << "[ERROR] no se pudo abrir el archivo" << endl;
	}
	while (!fShaderFile.eof())
	{
		string apoyoF;
		getline(fShaderFile, apoyoF);
		fragmentCode.append(apoyoF + "\n");
	}
	fShaderFile.close();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	const char* vertexShaderSoruce = vertexCode.c_str();
	
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1,&vertexShaderSoruce, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::FAILED\n" << infoLog << std::endl;
		return;
	};

	const char* fragmentShaderSoruce = fragmentCode.c_str();
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderSoruce, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::FAILED\n" << infoLog << std::endl;
		return;
	};

	_mIDprogram = glCreateProgram();
	glAttachShader(_mIDprogram, vertex);
	glAttachShader(_mIDprogram, fragment);
	glLinkProgram(_mIDprogram);

	glGetShaderiv(_mIDprogram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_mIDprogram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::FAILED\n" << infoLog << std::endl;
		return;
	};

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	mAllOK = true;
}



/*shadersFV.frag

FragColor = vec4(OurColor, 1.0);

*/
