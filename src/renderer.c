#include "renderer.h"

void generateVertexArray(struct VertexArray *v, int verticesCount, enum DrawOptions drawOp){
  glGenVertexArrays(1, &v->_id);
  v->_verticesCount = verticesCount;
  v->_drawOption = drawOp;
}

void generateBuffer(struct Buffer *buf, enum BufferType type){
  generateBufferd(buf, type, STATIC);
}

void generateBufferd(struct Buffer *buf, enum BufferType bufType, enum DrawType drawType){
  glGenBuffers(1, &buf->_id);
  buf->_type = bufType;
  buf->_drawType = drawType;
}
void bindVertexArray(struct VertexArray *v){
  glBindVertexArray(v->_id);
}

void bindBuffer(struct Buffer *buf){
  glBindBuffer(buf->_type, buf->_id);
}

void unbindBuffer(){
  glBindVertexArray(0);
}

void sendBufferData(struct Buffer *buf, struct BufferData *data){
  bindBuffer(buf);
  switch(data->_dataType){
  case FLOATING_POINT:
    glBufferData(buf->_type,
		 sizeof(struct Vertex)*data->_verticesCount,
		 data->_vertices,
		 buf->_drawType);
  }
}
void resendBufferData(struct Buffer *buf, struct Vertex *v, int n, int offset){
  bindBuffer(buf);
  glBufferSubData(buf->_type,
		  offset,
		  sizeof(struct Vertex) * n,
		  v);
}
void sendBufferDatae(struct Buffer *buf, GLuint *indices, GLuint count){
  bindBuffer(buf);
  glBufferData(buf->_type,
	       sizeof(indices) * count,
	       indices,
	       buf->_drawType);
}

void configData(struct Buffer *b, struct BufferData *v){
  int offset=0;
  
  switch(v->_dataType){
  case FLOATING_POINT:
    for(int i=0;i<v->_componentCount;i++){
      glVertexAttribPointer(i,
			    v->_componentSize[i],
			    GL_FLOAT,
			    GL_TRUE,// Force the false
			    v->_stride*sizeof(float),
			    (void*)offset);
      glEnableVertexAttribArray(i);
      offset += v->_componentSize[i]*sizeof(float);
    }
  }
}

void generateBufferData(struct BufferData *d,
			struct Vertex *v, GLuint vCount,
			enum DataType dt,
			GLuint stride,
			GLuint compCount,
			GLuint *comSizes){
  d->_vertices = v;
  d->_verticesCount = vCount;
  d->_dataType = dt;
  d->_componentCount = compCount;
  d->_stride = stride;
  d->_componentSize = comSizes;
}

void render(struct VertexArray *vao, struct ShaderProgram *prog){
  useShaderProgram(prog);
  bindVertexArray(vao);
  glDrawArrays(vao->_drawOption, 0, vao->_verticesCount);
}
 
