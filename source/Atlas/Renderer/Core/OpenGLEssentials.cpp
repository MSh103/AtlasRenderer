#include "OpenGLEssentials.h"

#include <Atlas/Core/Application.h>
#include <Atlas/Core/Log.h>
#include <Atlas/Graphics.h>


void GLClearError()
{
	while (glGetError() != GL_NO_ERROR && Atlas::Application::Get().IsRunning());
}

bool GLCheckError(const char* functionName, const char* filename, int lineNo)
{
	while (GLenum error = glGetError())
	{
		Atlas::Log::Core::Error("OpenGL Error: {}, {} {}:{}", error, functionName, filename, lineNo);
		return false;
	}

	return true;
}

uint32_t compileShader(const std::string& src, GLenum type)
{
	int success;
	char infoLog[512];

	uint32_t id;

	id = glCreateShader(type);
	const char* source = src.c_str();
	GLCall(glShaderSource(id, 1, &source, 0));
	GLCall(glCompileShader(id));
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		GLCall(glGetShaderInfoLog(id, 512, nullptr, infoLog));
		if (type == GL_VERTEX_SHADER)
			Atlas::Log::Core::Error("Vertex Shader Error: {}", infoLog);
		else if (type == GL_FRAGMENT_SHADER)
			Atlas::Log::Core::Error("Fragment Shader Error: {}", infoLog);
	}

	return id;
}

bool linkProgram(uint32_t& programID, uint32_t& vertID, uint32_t& fragID)
{
	int success;
	char infoLog[512];

	GLCall(glAttachShader(programID, vertID));
	GLCall(glAttachShader(programID, fragID));

	GLCall(glLinkProgram(programID));
	GLCall(glGetProgramiv(programID, GL_LINK_STATUS, &success));
	if (!success)
	{
		GLCall(glGetProgramInfoLog(programID, 512, nullptr, infoLog));
		Atlas::Log::Core::Error("Linking Error: {}", infoLog);

		return false;
	}
	return true;
}
