#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType)
{
    auto shader = ShaderUPtr(new Shader());
    if (!shader->LoadFile(filename, shaderType))
    {
        return nullptr;
    }
    return std::move(shader);
}

Shader::~Shader()
{
    if (m_shader = 0)
    {
        glDeleteShader(m_shader);
        m_shader = 0;
    }
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType)
{
    auto result = LoadTextFile(filename);
    if (!result.has_value())
    {
        return false;
    }
    auto& code = result.value();
    const char* codePtr = code.c_str();
    int32_t codeLength = (int32_t)code.length();

    m_shader = glCreateShader(shaderType);
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength);
    glCompileShader(m_shader);

    int scuccess = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &scuccess);

    if (!scuccess)
    {
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, NULL, infoLog);
        SPDLOG_ERROR("Shader compile error ({}): {}", filename, infoLog);
        glDeleteShader(m_shader);
        m_shader = 0;
        return false;
    }
    return true;
}