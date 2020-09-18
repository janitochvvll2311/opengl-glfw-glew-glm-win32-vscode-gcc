#pragma once
#include "GLEW/glew.h"

class GLarray {
    
    private:
        GLuint m_handle;

    public:
        GLuint Handle() const { return m_handle; }

        GLarray();
        ~GLarray();

        void Bind();

};