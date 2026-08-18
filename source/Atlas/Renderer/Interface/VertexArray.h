#pragma once

#include <numbers>
#include <string>
#include <vector>
#include <memory>

namespace Atlas
{
	class VertexBuffer;

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Use();

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);

		inline std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const { return m_VertexBuffers; }
	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	};
	
}
