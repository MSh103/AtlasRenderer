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

}