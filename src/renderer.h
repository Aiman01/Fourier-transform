#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>

#include "Include/glad/glad.h"
#include "shader.h"
#include "vertex.h"


//---------ENUMS
enum BufferType{
		ARRAY_BUFFER = GL_ARRAY_BUFFER,
		ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
};
enum DrawType{
	      STATIC = GL_STATIC_DRAW,
	      DYNAMIC = GL_DYNAMIC_DRAW,
	      STREAM = GL_STREAM_DRAW,
};
enum DataType{
	      FLOATING_POINT = GL_FLOAT,// due to clash with gl standard types
};
enum DrawOptions{
		 DRAW_POINTS = GL_POINTS,
		 DRAW_POINT  = GL_POINTS,
		 DRAW_LINES = GL_LINES,
		 DRAW_LINE  = GL_LINES,
		 DRAW_LINES_STRIP = GL_LINE_STRIP,
		 DRAW_LINE_STRIP  = GL_LINE_STRIP,
		 DRAW_TRIANGLES = GL_TRIANGLES,
		 DRAW_TRIANGLE  = GL_TRIANGLES,
		 DRAW_TRIANGLES_STRIP = GL_TRIANGLE_STRIP,
		 DRAW_TRIANGLE_STRIP  = GL_TRIANGLE_STRIP,
		 DRAW_TRIANGLES_FAN = GL_TRIANGLE_FAN,
		 DRAW_TRIANGLE_FAN  = GL_TRIANGLE_FAN

};

//---------STRUCTURES
struct VertexArray{
  GLuint _id;
  int _verticesCount;
  enum DrawOptions _drawOption;
};
struct Buffer{
  GLuint _id;
  enum BufferType _type;
  enum DrawType _drawType;
};
struct BufferData{
  struct Vertex *_vertices;
  enum DataType _dataType;
  GLuint _componentCount;
  GLuint _stride;
  GLuint *_componentSize;
  GLuint _verticesCount;
};

//---------PROTOTYPES
void generateVertexArray(struct VertexArray*, int , enum DrawOptions);
void generateBuffer(struct Buffer*, enum BufferType);
// NOTICE: the 'd' at the end which indicates the drawtype arg
void generateBufferd(struct Buffer*, enum BufferType, enum DrawType);
void bindVertexArray(struct VertexArray*);
void bindBuffer(struct Buffer*);
void unbindBuffer();
void sendBufferData(struct Buffer*, struct BufferData*);
void resendBufferData(struct Buffer*, struct Vertex*, int, int);
//NOTICE: the 'e'e at the end which indicates the indices arg
void sendBufferDatae(struct Buffer*, GLuint*, GLuint);
void configData(struct Buffer*, struct BufferData*);
//(data, vertices, verticesCount, vertices type, stride, components count, each component size, 
void generateBufferData(struct BufferData*, struct Vertex*, GLuint, enum DataType, GLuint, GLuint, GLuint*);
void render(struct VertexArray*, struct ShaderProgram*);

#endif // RENDERER_H
