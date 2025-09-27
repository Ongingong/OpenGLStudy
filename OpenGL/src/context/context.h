#pragma once
#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common/common.h"
#include "shader/shader.h"
#include "program/program.h"
#include "buffer/buffer.h"
#include "vertex_layout/vertex_layout.h"

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

    VertexLayoutUPtr m_vertexLayout;
    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;

    std::string vs_path = "src/shader/simple.vs";
    std::string fs_path = "src/shader/simple.fs";
};

#endif