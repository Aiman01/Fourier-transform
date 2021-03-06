// ------NOTE: MANAGE THE HEAP MEMORY IN OBJECTS.C FOR GENERATING OPJECTS
// https://stackoverflow.com/questions/37742358/sorting-points-to-form-a-continuous-line

#include "context.h"
#include "objects.h"
#include "complex.h"
#include "imgs/train.h"
#include <string.h>


float time=0;
int pos =0;
int __keyc=1;
int __keySpace=1;
int hideDrawing=0;
int hideCircles=0;

int
main(int argc, char **argv){
  // Setup context
  if(!initContext()) return -1;  

  // Setup coords
  int skip=6;
  int verticesSize = sizeof(drawing)/(sizeof(float)*2);
  int NUM_OF_LINES = (verticesSize)-4165;
  
  float path[NUM_OF_LINES][2];
  for(int i=0;i<NUM_OF_LINES;i++)
    path[i][0]=.0f, path[i][1]=.0f;
  struct Complex coords[NUM_OF_LINES];
  int j, i;
  for(i=0, j=0;i<verticesSize;j++,i+=skip){
    coords[j]=(struct Complex){drawing[i][0], drawing[i][1], 0, 0};/*
    coords[j]=(struct Complex){
			       (2.f*(drawing[i][0]+.5f)-1)/(float)WIDTH,
			       (2.f*(drawing[i][1]+.5f)-1)/(float)HEIGHT,
			       0, 0};*/
  }
  struct Complex waveVertices[NUM_OF_LINES];
  dft(waveVertices, coords, NUM_OF_LINES);

  
  // ---------SHADER------------
  // global shader
  char *verSrc  = "../src/defaultVertexShader.glsl";
  char *fragSrc = "../src/defaultFragShader.glsl";
  char *geoSrc  = "../src/defaultGeoShader.glsl";
  char *circleFragSrc = "../src/circleFragShader.glsl";
  
  struct ShaderProgram lineShader, waveShader, circleShader;
  generateShaderProgramVF(&circleShader, verSrc, circleFragSrc);
  generateShaderProgramVF(&lineShader, verSrc, fragSrc);
  generateShaderProgramVFG(&waveShader, verSrc, fragSrc, geoSrc);
  // --------OBJECTS-----------
  struct Object circles[NUM_OF_LINES];
  struct Object circleLines[NUM_OF_LINES];
  for(int i=0;i<NUM_OF_LINES;i++){
    generatePolygon(&circles[i], 90, DRAW_LINE_STRIP);
    float radius = waveVertices[i]._amplitude;
    scale(&circles[i]._transform, (vec3){radius, radius, 0});
    // Circle line
    generateLine(&circleLines[i]);
    translate(&circleLines[i]._transform, circles[i]._transform._location);
    scale(&circleLines[i]._transform, (vec3){radius, radius, 1.f});
  }

  // wave
  struct Object wave;
  generatePoint(&wave);
  translate(&wave._transform, (vec3){500, HEIGHT/2, -1});
  

  while(!contextShouldClose()){
    clearContext();

    // -------CONTROLS----------
        if(isKeyRelease(KEY(SPACE)))
      __keySpace=1;
    if(isKeyRelease(KEY(C)))
      __keyc=1;
    if(isKeyPress(KEY(C))&&__keyc){
      hideCircles=hideCircles?0:1;
      __keyc=0;
    }
    if(isKeyPress(KEY(SPACE))&&__keySpace){
      hideDrawing=hideDrawing?0:1;
      __keySpace=0;
    }

    // -----------DRAW----------
    // Big circle
    float x, y;
    x=WIDTH/2;y=HEIGHT/2;
    for(int i=0;i<NUM_OF_LINES;i++){
      float freq = waveVertices[i]._frequency;
      float radius = waveVertices[i]._amplitude;
      float phase = waveVertices[i]._phase;
      float n= freq * time + phase;
      // Circle
      translate(&circles[i]._transform, (vec3){x, y, -1});
      if(!hideCircles)
	drawPolygon(&circles[i], &circleShader);    
      // Line
      vec2 startPoint;
      vec2 endPoint;
      startPoint[0] = cos(n);
      startPoint[1] = sin(n);
      endPoint[0] = 0;
      endPoint[1] = 0;
      struct Vertex points[2]={{startPoint[0], startPoint[1], -1.f},
    			    {endPoint[0], endPoint[1], -1.f}};
      updateVertices(&circleLines[i], points, 2);
      translate(&circleLines[i]._transform, circles[i]._transform._location);
      if(!hideCircles)
	drawPolygon(&circleLines[i], &lineShader);
      
      x += radius*cos(n);
      y += radius*sin(n);
    }

    // wave
    char uniformName[32];
    if(pos==NUM_OF_LINES)pos=0;
    path[pos][0]=x;
    path[pos++][1]=y;
    for(int i=0;i<NUM_OF_LINES;i++){
      sprintf(uniformName, "verticesX[%i]", i);
      setFloat(&waveShader, uniformName, 2*(path[i][0]/WIDTH)-1);
      sprintf(uniformName, "verticesY[%i]", i);
      setFloat(&waveShader, uniformName, 2*(path[i][1]/HEIGHT)-1);
    }
    if(!hideDrawing)
      drawPolygon(&wave, &waveShader);

    float dt = 2 * M_PI / NUM_OF_LINES;
    time += dt;
    if(time>2*M_PI)time=0;
    updateContext();
  }
  // free data
  cleanContext();
  return 0;
}
