#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Include/cglm/cglm.h"

//--------STURCTURES
struct Transform{
  mat4 _modelMatrix;
  vec3 _location;
  float _rotation;
  vec3 _scale;
  vec3 _pivot;
};

//--------PROTOTYPES
void generateTransform(struct Transform*, vec3, float, vec3);
void generateMatrix(struct Transform*);
void translate(struct Transform*, vec3);
void rotate(struct Transform*, float);
void scale(struct Transform*, vec3);
void setPivot(struct Transform*, vec3);



#endif // _TRANSFORM_H
