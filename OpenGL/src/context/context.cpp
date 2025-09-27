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
	// Vertex data for a triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
         -0.5f, 0.5f, 0.0f
	};

    int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    m_vertexLayout = VertexLayout::Create();
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(vertices));

	m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(indices));

    // Create shaders
    ShaderPtr vertShader = Shader::CreateFromFile(vs_path, GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile(fs_path, GL_FRAGMENT_SHADER);

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

    return true;
}

void Context::Render()
{
    if (m_program)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        m_program->Use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}   