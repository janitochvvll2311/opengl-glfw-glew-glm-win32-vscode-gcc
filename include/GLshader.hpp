#pragma once
#include <string>
#include "GLEW/glew.h"

using namespace std;

class GLshader {

    private:
        GLuint m_handle;
        GLenum m_type;

    public:
        GLuint Handle() const { return m_handle; }
        GLuint Type()   const { return m_type; }
        
        GLshader(GLenum type);
        GLshader(GLenum type, const char *path);
        ~GLshader();

        void Source(const GLchar *const *source);
        void Compile();

        const GLchar *GetLog() const;

};