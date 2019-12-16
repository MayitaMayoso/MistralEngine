#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform float time;
uniform mat4 proj_matrix;
uniform float opacity;

flat out vec4 starColor;

void main(void)
{
vec4 newVertex = position;

newVertex.z += time;
newVertex.z = fract(newVertex.z);

float size = (20.0 * newVertex.z * newVertex.z);

starColor = smoothstep(40.0, 20.0, size) * color;

starColor = vec4(starColor.x, starColor.y, starColor.z, opacity);

newVertex.z = (999.9 * newVertex.z) - 1000.0;
gl_Position = proj_matrix * newVertex;
gl_PointSize = size;
}