#version 330 core

in vec3 vPosition;
in vec2 vTex;

out vec2 fTex;

uniform mat4 MVP;

void main() {
    vec4 v = vec4(vPosition, 1.0);
    vec4 r = MVP * v;
    gl_Position = r; 
    fTex = vTex;
}