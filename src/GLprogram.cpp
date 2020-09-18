#include "GLshader.hpp"
#include "GLprogram.hpp"

GLprogram::GLprogram() {
    m_handle = glCreateProgram();
}

GLprogram::GLprogram(const char *vertp, const char *fragp)
: GLprogram() {
    GLshader vert(GL_VERTEX_SHADER, vertp);
    GLshader frag(GL_FRAGMENT_SHADER, fragp);
    Attach(vert.Handle());
    Attach(frag.Handle());
    Link();
    Detach(vert.Handle());
    Detach(frag.Handle());
}

GLprogram::~GLprogram() {
    glDeleteProgram(m_handle);
}

void GLprogram::Attach(GLuint shader) {
    glAttachShader(m_handle, shader);
}

void GLprogram::Detach(GLuint shader) {
    glDetachShader(m_handle, shader);
}

void GLprogram::Link() {
    glLinkProgram(m_handle);
}

const GLchar *GLprogram::GetLog() {
    GLint result;
    GLint length;
    glGetProgramiv(m_handle, GL_LINK_STATUS, &result);
    glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &length);
    auto log = new GLchar[length + 1];
    glGetProgramInfoLog(m_handle, length, nullptr, log);
    return log;
}

void GLprogram::Use() {
    glUseProgram(m_handle);
}

GLint GLprogram::GetLocation(const GLchar *name) {
    return glGetAttribLocation(m_handle, name);
}

GLint GLprogram::GetUniformLocation(const GLchar *name) {
    return glGetUniformLocation(m_handle, name);
}

void GLprogram::SetUniformMat4(GLint location, GLsizei count, GLboolean traspose, const GLfloat *value) {
    glUniformMatrix4fv(location, count, traspose, value);
}

void GLprogram::SetUniformMat4(const GLchar *name, GLsizei count, GLboolean traspose, const GLfloat *value) {
    auto location = glGetUniformLocation(m_handle, name);
    glUniformMatrix4fv(location, count, traspose, value);
}
