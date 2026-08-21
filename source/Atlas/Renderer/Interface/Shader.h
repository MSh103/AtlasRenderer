#pragma once

#include <filesystem>
#include <string>
#include <numbers>
#include <vector>
#include <unordered_map>

#include "Atlas/Renderer/Core/Math.h"

namespace Atlas
{
	enum class ShaderType
	{
		None, Vertex, Fragment, Compute, Basic
	};
	const char* ShaderTypeToString(ShaderType type);

	class Shader
	{
	public:
		Shader();
		~Shader();

		void Use() const;

		bool LoadFromFile(ShaderType type = ShaderType::None, const std::filesystem::path& path = "");
		bool LoadFromString(ShaderType type = ShaderType::None, const std::string& src = "");

		bool LinkObjectsToProgram();

		void Upload(const std::string& location, const float& v);
		void Upload(const std::string& location, const glm::vec2& v);
		void Upload(const std::string& location, const glm::vec3& v);
		void Upload(const std::string& location, const glm::vec4& v);

		void Upload(const std::string& location, const int& v);
		void Upload(const std::string& location, const glm::ivec2& v);
		void Upload(const std::string& location, const glm::ivec3& v);
		void Upload(const std::string& location, const glm::ivec4& v);

		void Upload(const std::string& location, const unsigned int& v);
		void Upload(const std::string& location, const glm::uvec2& v);
		void Upload(const std::string& location, const glm::uvec3& v);
		void Upload(const std::string& location, const glm::uvec4& v);

		void Upload(const std::string& location, const glm::mat4& v);

	private:
		std::pair<bool, uint32_t> CompileShader(ShaderType type, const std::string& src);
		std::pair<std::pair<bool, uint32_t>, std::pair<bool, uint32_t>> CompileBasicShader(const std::string& src);
		int32_t GetUniformLocation(const std::string& location) const;


	private:
		mutable std::unordered_map<std::string, int32_t> m_UniformLocationCache;

		std::vector<uint32_t> m_ShaderObjects;
		uint32_t m_ProgramID;
	};
}