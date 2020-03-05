//GL_MAX_GEOMETRY_OUTPUT_VERTICES
#version 330 core

layout (points) in;
layout (line_strip, max_vertices = 1024) out;


uniform float verticesX[1024];
uniform float verticesY[1024];

void main(){
 for(int i=0;i<1024;i++){
  gl_Position=vec4(verticesX[i], verticesY[i], 0, 1);
  EmitVertex();
 }


 EndPrimitive();
}