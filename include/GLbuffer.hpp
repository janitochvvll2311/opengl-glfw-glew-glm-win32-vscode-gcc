#pragma once
#include "GLEW/glew.h"

class GLbuffer {

    private:
        GLuint m_handle;
        GLenum m_target;
        GLenum m_usage;

    public:
        GLuint Handle() const { return m_handle; }
        GLenum Target() const { return m_target; }
        GLenum Usage()  const { return m_usage; }

        GLbuffer(GLenum target, GLenum usage);
        ~GLbuffer();

        void Bind();
        void Data(GLsizeiptr size, const void *data);

};