#pragma once

#include <GL/glew.h>

class VertexBuffer
{
private:
    /* data */
    unsigned int m_RendererID;
public:
    VertexBuffer(const void* data, unsigned int size );
    ~VertexBuffer();

    void Bind() const ;
    void UnBind() const ;
};


