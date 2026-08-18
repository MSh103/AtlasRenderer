#include "IndexBuffer.h"

#include "Atlas/Renderer/Core/OpenGLEssentials.h"

namespace Atlas
{

	IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
		:m_Count(count)
	{
		GLCall(glCreateBuffers(1, &m_RendererID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	void IndexBuffer::Use()
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

}
