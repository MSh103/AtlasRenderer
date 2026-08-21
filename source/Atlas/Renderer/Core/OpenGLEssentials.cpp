#include "OpenGLEssentials.h"

#include <Atlas/Core/Application.h>
#include <Atlas/Core/Log.h>
#include <Atlas/Graphics.h>
#include "Atlas/Renderer/Interface/VertexBuffer.h"


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

GLenum ShaderDataTypeToOpenGLBaseType(Atlas::ShaderDataType type)
{
	switch (type)
	{
	case Atlas::ShaderDataType::Float:	     		return GL_FLOAT;
	case Atlas::ShaderDataType::Float2:			return GL_FLOAT;
	case Atlas::ShaderDataType::Float3:			return GL_FLOAT;
	case Atlas::ShaderDataType::Float4:			return GL_FLOAT;
	case Atlas::ShaderDataType::Mat3:			return GL_FLOAT;
	case Atlas::ShaderDataType::Mat4:			return GL_FLOAT;
	case Atlas::ShaderDataType::Int:			return GL_INT;
	case Atlas::ShaderDataType::Int2:			return GL_INT;
	case Atlas::ShaderDataType::Int3:			return GL_INT;
	case Atlas::ShaderDataType::Int4:			return GL_INT;
	case Atlas::ShaderDataType::Boolean:			return GL_BOOL;
	}
	return 0;
}
