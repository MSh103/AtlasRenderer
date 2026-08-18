#include "Buffers.h"

#include <Atlas/Core/Core.h>

#include "Atlas/Renderer/Core/OpenGLEssentials.h"

namespace Atlas
{

	VertexArray::VertexArray()
	{
		GLCall(glCreateVertexArrays(1, &m_RendererID));
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_RendererID));
	}

	void VertexArray::Use()
	{
		GLCall(glBindVertexArray(m_RendererID));
	}

}