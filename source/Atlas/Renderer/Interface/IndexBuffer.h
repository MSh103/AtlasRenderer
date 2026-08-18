#pragma once

#include <numbers>
#include <string>

namespace Atlas
{
	class IndexBuffer
	{
		IndexBuffer(uint32_t* indices, uint32_t count);
		~IndexBuffer();

		void Use();

		inline uint32_t GetCount() { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}