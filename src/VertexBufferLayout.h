#pragma once 

#include <vector>
#include <GL/glew.h>


struct VertexBufferElement
{
    /* data */
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type){
        // switch (type){
        //     case GL_FLOAT:          return 4;
        //     case GL_UNSIGNED_INT:   return 4;
        //     case GL_UNSIGNED_BYTE:  return 1;
        // }
        // assert(false);
        if(type == GL_FLOAT)
            return 4;
        else if (type == GL_UNSIGNED_INT)
            return 4;
        else if(type == GL_UNSIGNED_BYTE)
            return 1;        
        return 0;
    }
};


class VertexBufferLayout
{
private:
    /* data */
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout(/* args */): m_Stride(0){}

    template<typename T>
    void Push(unsigned int count){
        // static_assert(false);
    }

    inline unsigned int GetStride() const { return m_Stride; }
    inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
};

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count){
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_Stride += count*sizeof(GLfloat);
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count){
    m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_Stride += count*sizeof(GLuint);

}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count){
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_Stride += count*sizeof(GLbyte);

}

