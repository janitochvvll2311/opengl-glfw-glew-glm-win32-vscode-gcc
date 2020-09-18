#include "GLattrib.hpp"

GLattrib::GLattrib(GLuint _location, GLint _size, GLenum _type, GLboolean _normalized, GLsizeiptr _stride, void *_pointer)
: location(_location), size(_size), type(_type), normalized(_normalized), stride(_stride), pointer(_pointer) {}

void GLattrib::Enable() {
    glEnableVertexAttribArray(location);
}

void GLattrib::Use() {
    glVertexAttribPointer(location, size, type, normalized, stride, pointer);
}

void GLattrib::Disable() {
    glEnableVertexAttribArray(location);
}
