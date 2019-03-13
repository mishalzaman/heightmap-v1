#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

// Removing the tranlation matrix of the view matrix 
// by only taking the upper left 3x3 matrix
mat4 viewMatrix = mat4(mat3(view));

void main()
{
    TexCoords = aPos;
    vec4 pos = projection * viewMatrix * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  