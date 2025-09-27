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

private:
    Context() {};
    bool Init();
    ProgramPtr m_program{ nullptr };

    //  Buffer
    VertexLayoutUPtr m_vertexLayout;
    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;

	// Texture
    TextureUPtr m_texture;
	TextureUPtr m_texture2;

    std::string vs_path = "src/shader/simple.vs";
    std::string fs_path = "src/shader/simple.fs";
};

#endif