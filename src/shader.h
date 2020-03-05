#ifndef _SHADER_H
#define _SHADER_H

#include <stdio.h>
#include "Include/glad/glad.h"
#include "Include/cglm/cglm.h"
#include "transform.h"


#define bit(x) 1<<x

//------------STRUCTURES
struct Shader{
  unsigned int _id;
};
struct ShaderProgram{
  unsigned int _id;
};

//------------ENUMS
enum ShaderType{
		VERTEX = bit(0),
		FRAGMENT = bit(1),
		GEOMETRY = bit(2),
};


//------------PROTOTYPES
int generateShader(struct Shader*, enum ShaderType, char*);
// NOTICE: the 'g' at the end of the name which indicates geometery
int generateShaderProgramg(struct ShaderProgram*,
			  struct Shader*,
			  struct Shader*,
			  struct Shader*);
int generateShaderProgram(struct ShaderProgram*,
			  struct Shader*,
			  struct Shader*);
int generateShaderProgramVF(struct ShaderProgram*, char*, char*);
int generateShaderProgramVFG(struct ShaderProgram*, char*, char*, char*);
			  
int checkCompilationErrors(struct Shader*);
int checkLinkingErrors(struct ShaderProgram*);
void useShaderProgram(struct ShaderProgram*);
void unuseShaderProgram();
void deleteShader(struct Shader*);
void updateModelMatrix(struct ShaderProgram*, struct Transform*);
//---utilities
void setFloat(struct ShaderProgram*, const char*, float);
void setInt(struct ShaderProgram*, const char*, int);
void setVec2(struct ShaderProgram*, const char*, vec2);
void setVec3(struct ShaderProgram*, const char*, vec3);
void setMat4(struct ShaderProgram*, const char*, mat4);


#endif // _SHADER_H


