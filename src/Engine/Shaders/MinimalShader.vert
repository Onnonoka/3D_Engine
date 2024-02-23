#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

out vec3 vertexColor;

void main() {
    mat4 modelViewProjection = projection * view * transform;
    gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    vertexColor = aColor;
}
