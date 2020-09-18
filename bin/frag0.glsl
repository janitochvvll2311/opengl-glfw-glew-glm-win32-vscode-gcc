#version 330 core

in vec2 fTex;
out vec4 color;

uniform sampler2D xtex;
const vec3 xmask = vec3(1,1,1);

void main() {
    vec4 c = vec4(texture(xtex, fTex).rgb, 1.0);
    if(c.rgb == xmask) discard;
    color = c;
    color.a = 1.0;
}