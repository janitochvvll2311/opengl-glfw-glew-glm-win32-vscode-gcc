#pragma once
#include "GLEW/glew.h"

class GLattrib {

    public:
        GLuint location;
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLsizeiptr stride;
        void* pointer;

        GLattrib(GLuint _location, GLint _size, GLenum _type, GLboolean _normalized, GLsizeiptr _stride, void *_pointer);

        void Enable();
        void Use();
        void Disable();

};