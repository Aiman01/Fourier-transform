#ifndef _COMPLEX_H_
#define _COMPLEX_H_


struct Complex{
  float _re;
  float _im;
  float _frequency;
  float _phase;
  float _amplitude;
};


  
void dft(struct Complex*, struct Complex*, int);
void complexMult(struct Complex*, struct Complex*, struct Complex*);


#endif // _COMPLEX_H_
