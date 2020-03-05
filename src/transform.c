#include "transform.h"


void generateTransform(struct Transform* t, vec3 l, float r, vec3 s){
  translate(t, l);
  rotate(t, r);
  scale(t, s);
  setPivot(t, (vec3){l[0], l[1], l[2]});
}
void generateMatrix(struct Transform *t){
  glm_mat4_identity(t->_modelMatrix);
}
void translate(struct Transform *t, vec3 v) {
  glm_vec3_copy(v, t->_location);
  
  generateMatrix(t);
  glm_translate(t->_modelMatrix, v);
  glm_rotate_z(t->_modelMatrix,
	       t->_rotation,
	       t->_modelMatrix);
  glm_scale(t->_modelMatrix, t->_scale);
}
void rotate(struct Transform *t, float an) {
  t->_rotation = an;
  generateMatrix(t);
  glm_translate(t->_modelMatrix, t->_location);
  glm_rotate_z(t->_modelMatrix,
	       t->_rotation,
	       t->_modelMatrix);
  glm_scale(t->_modelMatrix, t->_scale);
}
void scale(struct Transform *t, vec3 s) {
  glm_vec3_copy(s, t->_scale);
  generateMatrix(t);
  glm_translate(t->_modelMatrix, t->_location);
  glm_rotate_z(t->_modelMatrix,
	       t->_rotation,
	       t->_modelMatrix);
  glm_scale(t->_modelMatrix, s);
}
void setPivot(struct Transform *t, vec3 p){
  glm_vec3_copy(p, t->_pivot);
}

