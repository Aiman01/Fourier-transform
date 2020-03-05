#include "complex.h"
#include <math.h>

void dft(struct Complex *X, struct Complex *x, int N){//X=dist, x=coords
  for(int k=0;k<N;k++){
    struct Complex sum;
    for(int n=0;n<N;n++){
      float phi = 2*M_PI*k*n/N;
      struct Complex temp;temp._re=cos(phi);temp._im=-sin(phi);
      struct Complex dist;
      complexMult(&x[n], &temp, &dist);
      sum._re += dist._re;
      sum._im -= dist._im;
    }
    sum._re /= N;
    sum._im /= N;
    float freq = k;
    float amp = sqrt(sum._re*sum._re+sum._im*sum._im);
    float phase = atan2(sum._im , sum._re);
    X[k]= (struct Complex){sum._re, sum._im, freq, phase, amp};
  }
}

void complexMult(struct Complex *a, struct Complex *b, struct Complex *dist){
  dist->_re = a->_re*b->_re - a->_im*b->_im;
  dist->_im = a->_re*b->_im + a->_im*b->_re;
}
