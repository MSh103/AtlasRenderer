#pragma once

#include <numbers>
#include <string>
#include <vector>

namespace Atlas
{

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Use();

	private:
		uint32_t m_RendererID;
	};

	
}
