#include "VertexArray.h"
#include "VertexBuffer.h"

#include <Atlas/Core/Core.h>

#include "Atlas/Renderer/Core/OpenGLEssentials.h"

namespace Atlas
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:	     		return GL_FLOAT;
		case ShaderDataType::Float2:			return GL_FLOAT;
		case ShaderDataType::Float3:			return GL_FLOAT;
		case ShaderDataType::Float4:			return GL_FLOAT;
		case ShaderDataType::Mat3:			return GL_FLOAT;
		case ShaderDataType::Mat4:			return GL_FLOAT;
		case ShaderDataType::Int:			return GL_INT;
		case ShaderDataType::Int2:			return GL_INT;
		case ShaderDataType::Int3:			return GL_INT;
		case ShaderDataType::Int4:			return GL_INT;
		case ShaderDataType::Boolean:			return GL_BOOL;
		}
		return 0;
	}

	VertexArray::VertexArray()
	{
		GLCall(glCreateVertexArrays(1, &m_RendererID));
		GLCall(glBindVertexArray(m_RendererID));
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_RendererID));
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