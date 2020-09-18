#include "GLbuffer.hpp"

GLbuffer::GLbuffer(GLenum target, GLenum usage)
: m_target(target), m_usage(usage) {
    glGenBuffers(1, &m_handle);
}

GLbuffer::~GLbuffer() {
    glDeleteBuffers(1, &m_handle);
}

void GLbuffer::Bind() {
    glBindBuffer(m_target, m_handle);
}

void GLbuffer::Data(GLsizeiptr size, const void* data) {
    glBufferData(m_target, size, data, m_usage);
}