#include "GLparameter.hpp"

GLparameter::GLparameter(GLenum _target, GLenum _name, GLint _value)
: target(_target), name(_name), value(_value) {}

void GLparameter::Use() {
    glTexParameteri(target, name, value);
}