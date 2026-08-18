#include "VertexArray.h"
#include "VertexBuffer.h"

#include <Atlas/Core/Log.h>

#include "Atlas/Renderer/Core/OpenGLEssentials.h"

namespace Atlas
{

	VertexArray::VertexArray()
	{
		GLCall(glCreateVertexArrays(1, &m_RendererID));
		GLCall(glBindVertexArray(m_RendererID));
		Atlas::Log::Core::Trace("Generated VertexArray: {}", m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_RendererID));
		Atlas::Log::Core::Trace("Deleted VertexArray: {}", m_RendererID);
	}

	void VertexArray::Use()
	{
		GLCall(glBindVertexArray(m_RendererID));
	}

	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		GLCall(glBindVertexArray(m_RendererID));

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			GLCall(glEnableVertexAttribArray(index));
			GLCall(glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset));
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

}