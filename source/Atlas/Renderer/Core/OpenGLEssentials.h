#pragma once

#include <Atlas/Core/Core.h>
#include <glad/glad.h>

#define GLCall(x) GLClearError();\
	x;\
	GLCheckError(#x, __FILE__, __LINE__);

void GLClearError();
bool GLCheckError(const char* functionName, const char* filename, int lineNo);
uint32_t compileShader(const std::string& src, GLenum type);
bool linkProgram(uint32_t& programID, uint32_t& vertID, uint32_t& fragID);