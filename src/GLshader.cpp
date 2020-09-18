#include <string>
#include <sstream>
#include <fstream>
#include "GLshader.hpp"

using namespace std;

GLshader::GLshader(GLenum type)
: m_type(type) {
    m_handle = glCreateShader(type);
}

GLshader::GLshader(GLenum type, const char *path)
: GLshader(type) {
    // Add log output (pending)
    string code;
    ifstream file(path);
    if(file.is_open()) {
        stringstream sstr;
        sstr << file.rdbuf();
        code = sstr.str();
        file.close();
    }
    auto source = code.c_str();
    Source(&source);
    Compile();
}

GLshader::~GLshader() {
    glDeleteShader(m_handle);
}

void GLshader::Source(const GLchar *const *source) {
    glShaderSource(m_handle, 1, source, nullptr);
}

void GLshader::Compile() {
    glCompileShader(m_handle);
}

const GLchar *GLshader::GetLog() const {
    GLint result;
    GLint length;
    glGetShaderiv(m_handle, GL_COMPILE_STATUS, &result);
    glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &length);
    auto log = new GLchar[length + 1];
    glGetShaderInfoLog(m_handle, length, nullptr, log);
    return log;
}