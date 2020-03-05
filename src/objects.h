#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "renderer.h"
#include "transform.h"
#include "shader.h"


struct Object{
  struct BufferData _data;
  struct VertexArray _vao;
  struct Buffer _vbo;
  struct Transform _transform;
};


void generatePolygon(struct Object*, int, enum DrawOptions);
void generateLine(struct Object*);
void generatePoint(struct Object*);
void changeVertices(struct Object*, struct Vertex*, int);
void updateVertices(struct Object*, struct Vertex*, int);
void updateVerticesWithOffset(struct Object*, struct Vertex*, int, int);

void drawPolygon(struct Object*, struct ShaderProgram*);


#endif //_OBJECTS_H
