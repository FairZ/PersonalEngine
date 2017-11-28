#include "Shader.h"
#include <fstream>
#include <vector>

Shader::Shader(std::string _name, const char* _vertTXT, const char* _fragTXT)
{
	m_name = _name;

	//load in the appropriate shaders from file
	std::string vertexString = LoadShader(_vertTXT);
	m_vertex = vertexString.c_str();
	std::string fragmentString = LoadShader(_fragTXT);
	m_fragment = fragmentString.c_str();

	//generate a program
	m_program = glCreateProgram();

	//create indexes and push shader data to the graphics card whilst attaching them to the program
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex,1,&m_vertex,NULL);
	glCompileShader(vertex);
	glAttachShader(m_program, vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &m_compiled);

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment,1,&m_fragment,NULL);
	glCompileShader(fragment);
	glAttachShader(m_program, fragment);

	if(m_compiled == GL_TRUE)
	{
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &m_compiled);
		if(m_compiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(fragment, maxLength, &maxLength, &errorLog[0]);

		}
	}
	else
	{
		GLint maxLength = 0;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(vertex, maxLength, &maxLength, &errorLog[0]);
	}

	//link the program together
	glLinkProgram(m_program);
	glUseProgram(m_program);

	//clear shaders now that the program is set up
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	//create a map of all uniforms used within the loaded shader
	GLint numOfUniforms;
	GLint sizeOfUniform;
	GLenum typeOfUniform;

	const GLsizei maxNameLength = 40;
	GLchar nameOfUniform[maxNameLength];
	GLsizei lengthOfName;

	glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &numOfUniforms);

	for(GLint i = 0; i < numOfUniforms; i++)
	{
		glGetActiveUniform(m_program, (GLuint) i, maxNameLength, &lengthOfName, &sizeOfUniform, &typeOfUniform, nameOfUniform);		
		m_uniforms.emplace(std::string(nameOfUniform),UniformInfo(glGetUniformLocation(m_program,std::string(nameOfUniform).c_str()),typeOfUniform));
	}
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

std::string Shader::LoadShader(const char* _fileName)
{
	std::string retVal;
	std::string line;
	//open a filestream to the specified location
	std::ifstream fileStream(_fileName, std::ios::in);

	/*error checking - TODO CHANGE TO DEBUG LOG
	if(!fileStream.is_open())
	{
		std::cout << "could not open: " << _fileName << std::endl;
		return "";
	}
	*/

	//while there is still data to read, add a line to the return string with appropriate line ending
	while(!fileStream.eof())
	{
		std::getline(fileStream,line);
		retVal.append(line + "\n");
	}

	//close the filestream
	fileStream.close();
	//return the final string
	return retVal;
}