#include "IndexBuffer.h"

#include "Atlas/Renderer/Core/OpenGLEssentials.h"

#include <Atlas/Core/Log.h>

namespace Atlas
{

	IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
		:m_Count(count)
	{
		GLCall(glCreateBuffers(1, &m_RendererID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
		Atlas::Log::Core::Trace("Generated IndexBuffer: {}", m_RendererID);
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
		Atlas::Log::Core::Trace("Deleted IndexBuffer: {}", m_RendererID);
	}

	void IndexBuffer::Use()
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

}
