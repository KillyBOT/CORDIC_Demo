#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cordic.h"

#define MAX_ITER 16

int main(int argc, char* argv[]){
  struct cnum a = {1,2};
  struct cnum b = {2,1};

  //print_cnum(c_mult(a,b));
  //print_cnum(c_conj(a));

  //printf("%f\n", cord_mag());

  printf("%.8f %.8f\n",c_mag(a),c_phase(a));

}

struct cnum c_mult(struct cnum a, struct cnum b){
  struct cnum c = {0,0};
  c.r = (a.r*b.r)-(a.i*b.i);
  c.i = (a.r*b.i)+(a.i*b.r);

  return c;
}

struct cnum c_conj(struct cnum c){
  c.i *= -1;
  return c;
}

double c_mag(struct cnum c){
  struct cnum r = {0,1}; //Rotation

  if(c.i > 0) c = c_mult(c,c_conj(r));
  else c = c_mult(c,r);

  r.r = 1;
  r.i = 1;

  print_cnum(c);

  for(int x = 0; x < MAX_ITER; x++){
    if(c.i > 0) c = c_mult(c,c_conj(r));
    else c = c_mult(c,r);

    r.i /= 2;
    print_cnum(c);
  }

  print_cnum(r);

  return c.r / cord_mag();
}

double c_phase(struct cnum c){
  struct cnum r = {0,1}; //Rotation
  double phase = 0;
  double phaseToAdd = 90;

  if(c.i > 0){
    c = c_mult(c,c_conj(r));
    phase += phaseToAdd;
  }
  else {
    c = c_mult(c,r);
    phase -= phaseToAdd;
  }

  phaseToAdd /= 2;

  r.r = 1;
  r.i = 1;

  //print_cnum(c);

  for(int x = 0; x < MAX_ITER; x++){
    if(c.i > 0){
      c = c_mult(c,c_conj(r));
      phase += phaseToAdd;
    }
    else {
      c = c_mult(c,r);
      phase -= phaseToAdd;
    }

    phaseToAdd /= 2;
    r.i /= 2;
  }

  return phase;
}

double cord_mag(){
  double mag = 1;
  double phase = 45;

  struct cnum c = {1,1};

  for(int x = 0; x < MAX_ITER; x++){
    //printf("Iter: %d\nPhase: %f\n", x + 1, phase);
    //print_cnum(c);

    mag *= sqrt((c.r * c.r) + (c.i * c.i));
    //printf("CORDIC mag: %.10f\n", mag);

    phase /= 2;
    c.i /= 2;
  }

  return mag;
}

void print_cnum(struct cnum c){
  printf("%f + %fi\n", c.r, c.i);
}
