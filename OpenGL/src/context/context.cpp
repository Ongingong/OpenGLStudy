#include "context.h"
#include "common/image.h"

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
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    };
    uint32_t indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };

    m_vertexLayout = VertexLayout::Create();
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 32);


    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
    m_vertexLayout->SetAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 3);
    m_vertexLayout->SetAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 6);

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

    auto image = Image::Load("resource/tex/container.jpg");
    if (!image)
        return false;
    m_texture = Texture::CreateFromImage(image.get());

    auto image2 = Image::Load("resource/tex/awesomeface.png");
    if (!image2)
        return false;
	m_texture2 = Texture::CreateFromImage(image2.get());

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture->Get());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_texture2->Get());

	m_program->Use();
	glUniform1i(glGetUniformLocation(m_program->Get(), "tex"), 0);
    glUniform1i(glGetUniformLocation(m_program->Get(), "tex2"), 1);

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