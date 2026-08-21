#pragma once

#include <Atlas/Core/Core.h>
#include <glad/glad.h>

#define GLCall(x) GLClearError();\
	x;\
	GLCheckError(#x, __FILE__, __LINE__);

namespace Atlas
{
	enum class ShaderDataType;
}

void GLClearError();
bool GLCheckError(const char* functionName, const char* filename, int lineNo);
GLenum ShaderDataTypeToOpenGLBaseType(Atlas::ShaderDataType type);