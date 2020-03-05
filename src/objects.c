#include "objects.h"
#include "renderer.h"
#include "vertex.h"
#include <math.h>


static struct Vertex* generateCircleVertices(int nfv){
  float _PI=2.f*M_PI;
  struct Vertex *circleVertices=(struct Vertex*)malloc(sizeof(struct Vertex) * (nfv+1));
  for(int i=0;i<(nfv+1);i++){
    circleVertices[i].x=cos(i*_PI/nfv);
    circleVertices[i].y=sin(i*_PI/nfv);
    circleVertices[i].z=0;}
  return circleVertices;
}

void generatePolygon(struct Object *obj, int nos, enum DrawOptions drawOp){
  struct Vertex *circleVertices=generateCircleVertices(nos);
    
  int Complen[] = {3};
  generateBufferData(&obj->_data, circleVertices, nos+1, FLOATING_POINT, 3, 1, Complen);

  generateVertexArray(&obj->_vao, nos+1, drawOp);
  generateBuffer(&obj->_vbo, ARRAY_BUFFER);
  
  bindVertexArray(&obj->_vao);
  
  bindBuffer(&obj->_vbo);
  sendBufferData(&obj->_vbo, &obj->_data);
  configData(&obj->_vbo, &obj->_data);
  
  generateTransform(&obj->_transform, (vec3){0, 0, -1}, 0, (vec3){1.f,1.f,1.f});
}

void generateLine(struct Object *obj){
  struct Vertex *vertices=(struct Vertex*)malloc(sizeof(struct Vertex)*2);
  vertices[0].x=1.f;
  vertices[0].y=0.f;
  vertices[0].z=0.f;
  vertices[1].x=1.f;
  vertices[1].y=0.f;
  vertices[1].z=0.f;

  int Complen[] = {3};
  generateBufferData(&obj->_data, vertices, 2/*vertices count*/, FLOATING_POINT, 3, 1, Complen);

  generateVertexArray(&obj->_vao, 2, DRAW_LINES);
  generateBufferd(&obj->_vbo, ARRAY_BUFFER, STREAM);
  
  bindVertexArray(&obj->_vao);
  
  bindBuffer(&obj->_vbo);
  sendBufferData(&obj->_vbo, &obj->_data);
  configData(&obj->_vbo, &obj->_data);
  
  generateTransform(&obj->_transform, (vec3){0, 0, -1}, 0, (vec3){1.f,1.f,1.f});
}

void generatePoint(struct Object *obj){
  struct Vertex *vertices=(struct Vertex*)malloc(sizeof(struct Vertex));
  vertices[0].x=1.f;
  vertices[0].y=0.f;
  vertices[0].z=0.f;
 
  int Complen[] = {3};
  generateBufferData(&obj->_data, vertices, 1/*vertices count*/, FLOATING_POINT, 3, 1, Complen);

  generateVertexArray(&obj->_vao, 1, DRAW_POINTS);
  generateBufferd(&obj->_vbo, ARRAY_BUFFER, STREAM);
  
  bindVertexArray(&obj->_vao);
  
  bindBuffer(&obj->_vbo);
  sendBufferData(&obj->_vbo, &obj->_data);
  configData(&obj->_vbo, &obj->_data);
  
  generateTransform(&obj->_transform, (vec3){0, 0, -1}, 0, (vec3){0.f,0.f,0.f});
}


void changeVertices(struct Object *obj, struct Vertex *v, int num){
  obj->_data._vertices=v;
  obj->_vao._verticesCount = num;
  resendBufferData(&obj->_vbo, v, num, 0);
}
void updateVertices(struct Object *obj, struct Vertex *v, int num){
  updateVerticesWithOffset(obj, v, num, 0); 
}
void updateVerticesWithOffset(struct Object *obj, struct Vertex *v, int num, int offset){
  resendBufferData(&obj->_vbo, v, num, offset);
}

void drawPolygon(struct Object *obj, struct ShaderProgram *shader){
  updateModelMatrix(shader, &obj->_transform);
  render(&obj->_vao, shader);
}
