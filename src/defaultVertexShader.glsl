#version 330 core

layout (location=0) in vec3 aPos;

uniform mat4 model;
uniform mat4 projection;

void main()
{
 gl_Position = projection * model * vec4(aPos.x, aPos.y, 0.f, 1.f);
 gl_PointSize = 1; // Only works when no geometry shader
}