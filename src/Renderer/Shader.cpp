#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GLCall.h"

Shader::Shader()
	: m_FilePath(""), m_RendererID(0)
{
	std::cout << "Shader created id:" << m_RendererID << std::endl;
}

Shader::Shader(const std::string & filepath, bool useGeometryShader)
	: m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);

	if (useGeometryShader)
		m_RendererID = CreateShader(source.VertexSource, source.GeometrySource, source.FragmentSource);
	else
		m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

	std::cout << "Shader created id:" << m_RendererID << std::endl;
}

Shader::~Shader()
{
	std::cout << "Shader created id:" << m_RendererID << std::endl;
	GLCall(glDeleteProgram(m_RendererID));
}

//Read shader file. Turn it into a string
ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, GEOMETRY = 1, FRAGMENT = 2
	};

	std::string line;
	std::stringstream ss[3];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("geometry") != std::string::npos)
				type = ShaderType::GEOMETRY;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			if (type != ShaderType::NONE)
				ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str(), ss[2].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);//creates a shader object. Gives back the id of that object
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));//Copies src code into shader object
	GLCall(glCompileShader(id));//The shader object created in the background is fully put together

	// TODO: Error handling
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));//puts info about the shader in result. 
												  //In this case info about the compile. Will return true or false
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));//returns number of characters in info log
		char* message = (char*)alloca(length * sizeof(char));//alloca() is used to dynamiclly create on the stack instead of heap
		GLCall(glGetShaderInfoLog(id, length, &length, message));//Returns the information log for a shader object
		std::cout << "Failed to compile shader!" << std::endl;
		if (type == GL_VERTEX_SHADER)
			std::cout << "VS" << std::endl;
		else if (type == GL_GEOMETRY_SHADER)
			std::cout << "GS" << std::endl;
		else if (type == GL_FRAGMENT_SHADER)
			std::cout << "FS" << std::endl;
		std::cout << message << std::endl;

		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();//Create program object and give back the id for it
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);//Get the id of the shader object
	unsigned int gs = CompileShader(GL_GEOMETRY_SHADER, geometryShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));//Attaches a shader object to a program object
	GLCall(glAttachShader(program, gs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));//Links the program. Any shaders attached are linked with this
	GLCall(glValidateProgram(program));//Validates a program object

	//Shaders are now in the program and the temp ones can be deleted
	GLCall(glDeleteShader(vs));//frees memory
	GLCall(glDeleteShader(gs));
	GLCall(glDeleteShader(fs));

	return program;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();//Create program object and give back the id for it
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);//Get the id of the shader object
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));//Attaches a shader object to a program object
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));//Links the program. Any shaders attached are linked with this
	GLCall(glValidateProgram(program));//Validates a program object

	//Shaders are now in the program and the temp ones can be deleted
	GLCall(glDeleteShader(vs));//frees memory
	GLCall(glDeleteShader(fs));

	return program;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetFilePath(const std::string& filepath)
{
	m_FilePath = filepath;
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.GeometrySource, source.FragmentSource);
}

void Shader::SetUniform1i(const std::string & name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string & name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1iv(const std::string& name, int size, int* value)
{
	GLCall(glUniform1iv(GetUniformLocation(name), size, value));
}

void Shader::SetUniform2f(const std::string& name, float v1, float v2)
{
	GLCall(glUniform2f(GetUniformLocation(name), v1, v2));
}

void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string & name, const glm::mat4 & matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string & name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	//int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
	m_UniformLocationCache[name] = location;
	return location;
}

