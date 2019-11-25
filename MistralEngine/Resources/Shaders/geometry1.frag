#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

void buildTriangle(vec4 position) {
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);
    EmitVertex();
    gl_Position = position + vec4(0.2, 0.2, 0.0, 0.0);
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0); 
    EmitVertex();
    EndPrimitive();
}

void main() {
    buildTriangle(gl_in[0].gl_Position);
}  