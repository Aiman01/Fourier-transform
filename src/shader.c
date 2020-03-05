#include "shader.h"
#include "resourcesManager.h"

int generateShader(struct Shader *shader, enum ShaderType type, char *path){
  char *src = rdfl(path);
  if(!src) { fprintf(stderr, "Could not read file \"%s\"\n", path);return 0;}
  switch(type){
  case VERTEX:
    shader->_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader->_id, 1,(const char**)&src, NULL);
    glCompileShader(shader->_id);
    if(!checkCompilationErrors(shader)){
      fprintf(stderr, "Could not compile vertex shader...\n");
      free(src);
      return 0;
    }
    break;

  case FRAGMENT:
    shader->_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader->_id, 1, (const char**)&src, NULL);
    glCompileShader(shader->_id);
    if(!checkCompilationErrors(shader)){
      fprintf(stderr, "Could not compile fragment shader...\n");
      free(src);
      return 0;
    }
    break;

  case GEOMETRY:
    shader->_id = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(shader->_id, 1, (const char**)&src, NULL);
    glCompileShader(shader->_id);
    if(!checkCompilationErrors(shader)){
      fprintf(stderr, "Could not compile geometery shader...\n");
      free(src);
      return 0;
    }
    break;
  default: fprintf(stderr, "Unknown shader type...\n"); free(src); break;
  }
  free(src);
  return 1;
}

int generateShaderProgram(struct ShaderProgram *prog,
			  struct Shader *ver,
			  struct Shader *frag){
  return generateShaderProgramg(prog, ver, frag, NULL);
}

int generateShaderProgramg(struct ShaderProgram *prog,
			  struct Shader *ver,
			  struct Shader *frag,
			  struct Shader *geo){
  prog->_id = glCreateProgram();
  glAttachShader(prog->_id, ver->_id);
  glAttachShader(prog->_id, frag->_id);
  if(geo)
    glAttachShader(prog->_id, geo->_id);
  glLinkProgram(prog->_id);
  if(!checkLinkingErrors(prog)){
    fprintf(stderr, "Could not link shaders...\n");
    return 0;
  }
  deleteShader(ver);
  deleteShader(frag);
  if(geo)
    deleteShader(geo);

  return 1;
  
}
int generateShaderProgramVF(struct ShaderProgram *prog, char *verSrc, char *fragSrc){
  generateShaderProgramVFG(prog, verSrc, fragSrc, NULL);
}
int generateShaderProgramVFG(struct ShaderProgram *prog, char *verSrc, char *fragSrc, char *geoSrc){
  struct Shader ver, frag, geo;
  if(verSrc  && !generateShader(&ver, VERTEX, verSrc))
    fprintf(stderr, "ver shader not created\n");
  if(fragSrc && !generateShader(&frag, FRAGMENT, fragSrc))
    fprintf(stderr, "frag shader not created\n");
  if(geoSrc && !generateShader(&geo, GEOMETRY, geoSrc)){
    fprintf(stderr, "frag shader not created\n");return 0;}
  if(!geoSrc){
    if(!generateShaderProgram(prog, &ver, &frag))
      fprintf(stderr, "shaderprog not created\n");
  }
  else
    if(!generateShaderProgramg(prog, &ver, &frag, &geo))
      fprintf(stderr, "shaderprog not created\n");
  // This shouldn't be here!!
  useShaderProgram(prog);
  mat4 ortho;
  glm_ortho(0, 1280, 0, 720, .1f, 100.f, ortho);
  setMat4(prog, "projection", ortho);
  // clean up shaders
  deleteShader(&ver);deleteShader(&frag);deleteShader(&geo);
}
int checkCompilationErrors(struct Shader *shader){
  int status;
  char log[512];
  glGetShaderiv(shader->_id, GL_COMPILE_STATUS, &status);
  if(!status){
    glGetShaderInfoLog(shader->_id, 512, NULL, log);
    fprintf(stderr, "ERROR::SHADER::COMPILATION_FAILED: %s\n", log);
    return 0;
  }
  return 1;
}

int checkLinkingErrors(struct ShaderProgram *prog){
  int status;
  char log[512];
  glGetProgramiv(prog->_id, GL_LINK_STATUS, &status);
  if(!status){
    glGetProgramInfoLog(prog->_id, 512, NULL, log);
    fprintf(stderr, "ERROR::PROGRAM::LINK_FAILED: %ps\n", log);
    return 0;
  }
  return 1;
}

void useShaderProgram(struct ShaderProgram *prog){
  glUseProgram(prog->_id);
}
void unuseShaderProgram(){
  glUseProgram(0);
}
void deleteShader(struct Shader *shader){ glDeleteShader(shader->_id); }

void updateModelMatrix(struct ShaderProgram *shader, struct Transform *trans){
  setMat4(shader, "model", trans->_modelMatrix);
}
void setFloat(struct ShaderProgram *prog, const char *name, float value){
  useShaderProgram(prog);
  glUniform1f(glGetUniformLocation(prog->_id, name), value); 
} 

void setInt(struct ShaderProgram *prog, const char *name, int value){
  useShaderProgram(prog);
  glUniform1i(glGetUniformLocation(prog->_id, name), value); 
}
void setVec2(struct ShaderProgram *prog, const char *name, vec2 v){
  useShaderProgram(prog);
  glUniform2fv(glGetUniformLocation(prog->_id, name), 1, (float*)v);
}
void setVec3(struct ShaderProgram *prog, const char *name, vec3 v){
  useShaderProgram(prog);
  glUniform3fv(glGetUniformLocation(prog->_id, name), 1, (float*)v);
}
void setMat4(struct ShaderProgram *prog, const char *name, mat4 m){
  useShaderProgram(prog);
  glUniformMatrix4fv(glGetUniformLocation(prog->_id, name), 1, GL_FALSE, (float*)m);
}
