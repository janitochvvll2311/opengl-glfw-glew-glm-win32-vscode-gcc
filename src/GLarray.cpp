#include "GLarray.hpp"

GLarray::GLarray() {
    glGenVertexArrays(1, &m_handle);
}

GLarray::~GLarray() {
    glDeleteVertexArrays(1, &m_handle);
}

void GLarray::Bind() {
    glBindVertexArray(m_handle);
}