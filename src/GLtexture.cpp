#include "GLtexture.hpp"

GLtexture::GLtexture(GLenum target, GLint level, GLint format)
: m_target(target), m_level(level), m_format(format) {
    glGenTextures(1, &m_handle);
}

GLtexture::~GLtexture() {
    glDeleteTextures(1, &m_handle);
}

void GLtexture::Bind() {
    glBindTexture(m_target, m_handle);
}

void GLtexture::Source2D(GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *source) {
    glTexImage2D(m_target, m_level, m_format, width, height, border, format, type, source);
}

void GLtexture::GenerateMipmap() {
    glGenerateMipmap(m_target);
}