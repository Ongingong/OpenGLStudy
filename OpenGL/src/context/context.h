#pragma once
#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common/common.h"
#include "shader/shader.h"
#include "program/program.h"
#include "buffer/buffer.h"
#include "vertex_layout/vertex_layout.h"
#include "texture/texture.h"

CLASS_PTR(Context)
class Context
{
public:
    static ContextUPtr Create();
    void Render();
	void ProcessInput(GLFWwindow* window);
	void Reshape(int width, int height);
    void MouseMove(double x, double y);
    void MouseButton(int button, int action, double x, double y);

private:
    Context() {};
    bool Init();
    ProgramPtr m_program{ nullptr };

    // Window
    int m_width{ 1920 };
    int m_height{ 1080 };

    //  Buffer
    VertexLayoutUPtr m_vertexLayout;
    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;

	// Texture
    TextureUPtr m_texture;
	TextureUPtr m_texture2;

    // Color
    glm::vec4 m_clearColor{ glm::vec4(0.18f, 0.18f, 0.18f, 1.0f) };

    // Camera
    float m_cameraPitch{ 0.0f };
    float m_cameraYaw{ 0.0f };
    glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    bool m_cameraControl{ false };
    glm::vec2 m_prevMousePos{ glm::vec2(0.0f) };

    std::string vs_path = "src/shader/simple.vs";
    std::string fs_path = "src/shader/simple.fs";
};

#endif