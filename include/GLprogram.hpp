#pragma once
#include "GLEW/glew.h"

class GLprogram {

    private:
        GLuint m_handle;

    public:
        GLuint Handle() const { return m_handle; }

        GLprogram();
        GLprogram(const char *vert, const char *frag);
        ~GLprogram();
 
        void Attach(GLuint shader);
        void Detach(GLuint shader);

        void Link();
        const GLchar *GetLog();

        void Use();
        GLint GetLocation(const GLchar *name);
        GLint GetUniformLocation(const GLchar *name);

        void SetUniformMat4(GLint location, GLsizei count, GLboolean traspose, const GLfloat *value);
        void SetUniformMat4(const GLchar *name, GLsizei count, GLboolean traspose, const GLfloat *value);

};