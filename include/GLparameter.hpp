#pragma once
#include "GLEW/glew.h"

class GLparameter {

    public:
        GLenum target;
        GLenum name;
        GLint value;

        GLparameter(GLenum _target, GLenum _name, GLint _value);

        void Use();

};