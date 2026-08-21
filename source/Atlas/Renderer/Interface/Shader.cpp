#include "Shader.h"

#include "Atlas/Renderer/Core/OpenGLEssentials.h"
#include <Atlas/Core/Log.h>

#include <fstream>
#include <sstream>

static std::string ReadFileAsString(const std::filesystem::path& filepath)
{
	std::string result;
	std::ifstream in(filepath, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		result.resize((size_t)in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	else
		Atlas::Log::Core::Error("Could Not Open File '{}'", filepath);

	return result;
}

namespace Atlas
{

	Shader::Shader()
	{
		GLCall(m_ProgramID = glCreateProgram());
		Log::Core::Trace("Created Shader Program: {}", m_ProgramID);
	}

	Shader::~Shader()
	{
		Log::Core::Trace("Deleted Shader Program: {}", m_ProgramID);
		GLCall(glDeleteProgram(m_ProgramID));
	}

	void Shader::Use() const
	{
		GLCall(glUseProgram(m_ProgramID));
	}

	bool Shader::LoadFromFile(ShaderType type /*= ShaderType::None*/, const std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path))
		{
			Log::Core::Error("Failed to locate Shader File!");
			return false;
		}

		std::string src = ReadFileAsString(path);

		return LoadFromString(type, src);
	}

	bool Shader::LoadFromString(ShaderType type /*= ShaderType::None*/, const std::string& src)
	{
		if (type == ShaderType::Basic)
		{
			auto result = CompileBasicShader(src);

			bool vertexStatus = result.first.first;
			uint32_t vertexShaderObject = result.first.second;

			bool fragmentStatus = result.second.first;
			uint32_t framgentShaderObject = result.second.second;

			if (!vertexStatus || !fragmentStatus)
				return false;
			
			m_ShaderObjects.push_back(vertexShaderObject);
			m_ShaderObjects.push_back(framgentShaderObject);
			return true;
		}
		else {
			auto [success, shader] = CompileShader(type, src);
			if (!success)
				return false;

			m_ShaderObjects.push_back(shader);
			return true;
		}

		return true;
	}

	bool Shader::LinkObjectsToProgram()
	{
		int success;
		char infoLog[512];

		for (uint32_t so : m_ShaderObjects)
		{
			GLCall(glAttachShader(m_ProgramID, so));
		}

		GLCall(glLinkProgram(m_ProgramID));
		GLCall(glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success));
		if (!success)
		{
			GLCall(glGetProgramInfoLog(m_ProgramID, 512, nullptr, infoLog));
			Log::Core::Error("Linking Error: {}", infoLog);

			return false;
		}

		for (uint32_t so : m_ShaderObjects)
		{
			GLCall(glDeleteShader(so));
		}

		return true;
	}

	void Shader::Upload(const std::string& location, const float& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniform1f(id, v));
	}

	void Shader::Upload(const std::string& location, const glm::vec2& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniform2f(id, v.x, v.y));
	}

	void Shader::Upload(const std::string& location, const glm::vec3& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniform3f(id, v.x, v.y, v.z));
	}

	void Shader::Upload(const std::string& location, const glm::vec4& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniform4f(id, v.x, v.y, v.z, v.w));
	}

	void Shader::Upload(const std::string& location, const int& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniform1i(id, v));
	}

	void Shader::Upload(const std::string& location, const glm::ivec2& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniform2i(id, v.x, v.y));
	}

	void Shader::Upload(const std::string& location, const glm::ivec3& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniform3i(id, v.x, v.y, v.z));
	}

	void Shader::Upload(const std::string& location, const glm::ivec4& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniform4i(id, v.x, v.y, v.z, v.w));
	}

	void Shader::Upload(const std::string& location, const unsigned int& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniform1ui(id, v));
	}

	void Shader::Upload(const std::string& location, const glm::uvec2& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniform2ui(id, v.x, v.y));
	}

	void Shader::Upload(const std::string& location, const glm::uvec3& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniform3ui(id, v.x, v.y, v.z));
	}

	void Shader::Upload(const std::string& location, const glm::uvec4& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniform4ui(id, v.x, v.y, v.z, v.w));
	}

	void Shader::Upload(const std::string& location, const glm::mat4& v)
	{
		int32_t id = GetUniformLocation(location);
		GLCall(glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(v)));
	}

	std::pair<bool, uint32_t> Shader::CompileShader(ShaderType type /*= ShaderType::None*/, const std::string& src)
	{
		GLenum shaderType;
		switch (type)
		{
		case Atlas::ShaderType::None:
		{
			AT_ASSERT(false, "Not supported ShaderType!");
			break;
		}
		case Atlas::ShaderType::Vertex:
		{
			shaderType = GL_VERTEX_SHADER;
			break;
		}
		case Atlas::ShaderType::Fragment:
		{
			shaderType = GL_FRAGMENT_SHADER;
			break;
		}
		case Atlas::ShaderType::Compute:
		{
			shaderType = GL_COMPUTE_SHADER;
			break;
		}
		default:
			break;
		}

		GLCall(GLuint shader = glCreateShader(shaderType));

		const char* source = src.c_str();
		GLCall(glShaderSource(shader, 1, &source, nullptr));
		GLCall(glCompileShader(shader));
		
		GLint compiled = GL_FALSE;
		GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled));
		if (!compiled)
		{
			char infoLog[512];
			GLCall(glGetShaderInfoLog(shader, 512, nullptr, infoLog));
			Log::Core::Error("{} Shader Compilation Error: {}", ShaderTypeToString(type), infoLog);			
			return { false, 0 };
		}

		return { true, shader };
	}

	std::pair<std::pair<bool, uint32_t>, std::pair<bool, uint32_t>> Shader::CompileBasicShader(const std::string& src)
	{
		std::string vertexSource;
		std::string fragmentSource;

		enum class Type : int
		{
			None = -1, Vertex = 0, Fragment = 1
		};

		Type type = Type::None;

		std::istringstream stream(src);
		std::stringstream ss[2];
		std::string line;
		while (std::getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = Type::Vertex;
				else if (line.find("fragment") != std::string::npos)
					type = Type::Fragment;
			}
			else
			{
				ss[(int)type] << line << "\n";
			}
		}
		
		vertexSource = ss[0].str();
		fragmentSource = ss[1].str();

		auto [vStatus, vSO] = CompileShader(ShaderType::Vertex, vertexSource);
		auto [fStatus, fSO] = CompileShader(ShaderType::Fragment, fragmentSource);

		return { {vStatus, vSO}, {fStatus, fSO} };
	}

	int32_t Shader::GetUniformLocation(const std::string& location) const
	{
		if (m_UniformLocationCache.find(location) != m_UniformLocationCache.end())
			return m_UniformLocationCache[location];

		GLCall(int32_t id = glGetUniformLocation(m_ProgramID, location.c_str()));
		Log::Core::Trace("Uniform Cached '{}': {}", location, id);

		m_UniformLocationCache[location] = id;

		return m_UniformLocationCache[location];
	}

	const char* ShaderTypeToString(ShaderType type)
	{
		switch (type)
		{
		case Atlas::ShaderType::None:		return "None";
		case Atlas::ShaderType::Vertex:		return "Vertex";
		case Atlas::ShaderType::Fragment:	return "Fragment";
		case Atlas::ShaderType::Compute:	return "Compute";
		case Atlas::ShaderType::Basic:		return "Basic";
		default:				return "Unknown";
		}
	}

}