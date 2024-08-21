// JE_TRANSLATE
#version 420

layout(location = 0) out vec4 c_final;
layout(location = 2) in vec3 vnorm;

layout(set = 0, binding = 0) uniform UBO { // JE_TRANSLATE
    mat4 viewMatrix;
    mat4 _2dProj;
    mat4 _3dProj;
    vec3 cameraPos;
    vec3 cameraDir;
    vec2 screenSize;
};

void main() {
    c_final = vec4(0.45, 0.8, 0.55, 0.15);
}