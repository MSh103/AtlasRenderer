#include "VertexBuffer.h"

#include "Atlas/Renderer/Core/OpenGLEssentials.h"

#include <Atlas/Core/Log.h>

namespace Atlas
{

	uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:      return 4;
		case ShaderDataType::Float2:     return 4 * 2;
		case ShaderDataType::Float3:     return 4 * 3;
		case ShaderDataType::Float4:     return 4 * 4;
		case ShaderDataType::Mat3:	 return 4 * 3 * 3;
		case ShaderDataType::Mat4:	 return 4 * 4 * 4;
		case ShaderDataType::Int:	 return 4;
		case ShaderDataType::Int2:	 return 4 * 2;
		case ShaderDataType::Int3:	 return 4 * 3;
		case ShaderDataType::Int4:	 return 4 * 4;
		case ShaderDataType::Boolean:	 return 1;
		}
		return 0;
	}

	uint32_t BufferElement::GetComponentCount() const
	{
		switch (Type)
		{
		case ShaderDataType::Float:			return 1;
		case ShaderDataType::Float2:		return 2;
		case ShaderDataType::Float3:		return 3;
		case ShaderDataType::Float4:		return 4;
		case ShaderDataType::Mat3:			return 3 * 3;
		case ShaderDataType::Mat4:			return 4 * 4;
		case ShaderDataType::Int:			return 1;
		case ShaderDataType::Int2:			return 2;
		case ShaderDataType::Int3:			return 3;
		case ShaderDataType::Int4:			return 4;
		case ShaderDataType::Boolean:		return 1;
		}
		return 0;
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements), m_Stride(0)
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

	VertexBuffer::VertexBuffer(void* data, uint32_t size)
	{
		GLCall(glGenBuffers(1, &m_RendererID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		Atlas::Log::Core::Trace("Generated VertexBuffer: {}", m_RendererID);
	}

	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
		Atlas::Log::Core::Trace("Deleted VertexBuffer: {}", m_RendererID);
	}

	void VertexBuffer::Use()
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}
}