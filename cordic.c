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

  printf("%.8f %.8f\n",c_mag(b),c_phase(b));

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

  for(int x = 0; x < MAX_ITER; x++){
    if(c.i > 0) c = c_mult(c,c_conj(r));
    else if(c.i < 0)c = c_mult(c,r);
    else return c.r / cord_mag(x);

    r.i /= 2;
  }

  return c.r / cord_mag(MAX_ITER);
}

double c_phase(struct cnum c){
  struct cnum r = {0,1}; //Rotation
  double phase = 0;
  double temp;
  double atan_table[16] = {
    45,
    26.56505118,
    14.03624347,
    7.12501635,
    3.57633437,
    1.78991061,
    0.89517371,
    0.44761417,
    0.2238105,
    0.11190568,
    0.05595289,
    0.02797645,
    0.01398823,
    0.00699411,
    0.00349706,
    0.00174853};

  if(c.i > 0){
    c = c_mult(c,c_conj(r));
    phase += 90;
  }
  else if (c.i < 0){
    c = c_mult(c,r);
    phase -= 90;
  } else {
    return 0;
  }

  r.r = 1;

  for(int x = 0; x < MAX_ITER; x++){
    printf("%lf\n", phase);
    print_cnum(c);
    if(c.i > 0){
      c = c_mult(c,c_conj(r));
      phase += atan_table[x];
    }
    else if(c.i < 0){
      c = c_mult(c,r);
      phase -= atan_table[x];
    } else {
      return phase;
    }

    r.i /= 2;

  }

  return phase;
}

double cord_mag(int iter){
  double mag = 1;
  double phase = 45;

  struct cnum c = {1,1};

  for(int x = 0; x < iter; x++){
    //printf("Iter: %d\nPhase: %f\n", x + 1, phase);
    //print_cnum(c);

    mag *= sqrt((c.r * c.r) + (c.i * c.i));
    //printf("CORDIC mag: %.10f\n", mag);

    phase /= 2;
    c.i /= 2;
  }

  return mag;
}

double c_sine(double theta){
  struct cnum; //Rotation
  double phase;
  double temp;
  double atan_table[16] = {
    45,
    26.56505118,
    14.03624347,
    7.12501635,
    3.57633437,
    1.78991061,
    0.89517371,
    0.44761417,
    0.2238105,
    0.11190568,
    0.05595289,
    0.02797645,
    0.01398823,
    0.00699411,
    0.00349706,
    0.00174853};

  if(theta > 90){
    phase = 90;
  }
  else if (theta < 90){
    c = c_mult(c,r);
    phase = -90;
  } else {
    return 0;
  }

  r.r = 1;

  for(int x = 0; x < MAX_ITER; x++){
    printf("%lf\n", phase);
    print_cnum(c);
    if(c.i > 0){
      c = c_mult(c,c_conj(r));
      phase += atan_table[x];
    }
    else if(c.i < 0){
      c = c_mult(c,r);
      phase -= atan_table[x];
    } else {
      return phase;
    }

    r.i /= 2;

  }

  return phase;
}

void print_cnum(struct cnum c){
  printf("%f + %fi\n", c.r, c.i);
}
