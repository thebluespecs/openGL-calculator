#pragma once

#include <GL/glew.h>

class IndexBuffer
{
private:
    /* data */
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer( unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    inline unsigned int GetCount() const {
        return m_Count;
    }


};


