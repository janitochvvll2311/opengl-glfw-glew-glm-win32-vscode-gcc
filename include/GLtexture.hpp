#pragma once
#include "GLEW/glew.h"

class GLtexture {

    private:
        GLuint m_handle;
        GLenum m_target;
        GLint m_level;
        GLint m_format;

    public:
        GLuint Handle() const { return m_handle; }
        GLenum Target() const { return m_target; }
        GLint Level() const { return m_level; }

        GLtexture(GLenum target, GLint level, GLint format);
        ~GLtexture();

        void Bind();
        void Source2D(GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *source);
        void GenerateMipmap();

};