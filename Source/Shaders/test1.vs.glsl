#version 460 core
#extension GL_ARB_explicit_uniform_location : enable
layout (location = 0) in vec3 inPos;

layout (location = 0) uniform mat4 worldViewMat;
layout (location = 1) uniform mat4 projMat;

void main()
{
    gl_Position = projMat * worldViewMat * vec4(inPos, 1.0);
}
