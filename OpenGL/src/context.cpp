#include "context.h"

ContextUPtr Context::Create()
{
    auto context = ContextUPtr(new Context());
    if (!context->Init())
    {
        return nullptr;
    }
    return std::move(context);
}

bool Context::Init()
{
    // Create shaders
    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    if (!vertShader || !fragShader)
    {
        return false;
    }
    spdlog::info("Vertex Shader ID : {}", vertShader->Get());
    spdlog::info("Fragment Shader ID : {}", fragShader->Get());

    // Create program
    m_program = Program::Create({ vertShader, fragShader });
    if (!m_program)
    {
        return false;
    }
    spdlog::info("Program ID : {}", m_program->Get());
    glClearColor(0.18f, 0.18f, 0.18f, 1.0f);

    // Setup vertex data temporarily
    uint32_t vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return true;
}

void Context::Render()
{
    if (m_program)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(m_program->Get());
        glDrawArrays(GL_POINTS, 0, 1);
    }
}