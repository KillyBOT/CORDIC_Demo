#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cordic.h"

#define MAX_ITER 60

int main(int argc, char* argv[]){
  struct cnum a = {1,2};
  struct cnum b = {2,1};

  //print_cnum(c_mult(a,b));
  //print_cnum(c_conj(a));

  //printf("%f\n", cord_mag());

  //printf("%.8f %.8f\n",c_mag(b),c_phase(b));
  printf("%f\n", sine(30));

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
  else if(c.i < 0) c = c_mult(c,r);
  else return c.i;

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

double sine(double theta){
  struct cnum c;
  struct cnum r = {1,1}; //Rotation
  double phase = 0;
  double atan_table[MAX_ITER] = {
    45.0000000000000000,
    26.5650511770779900,
    14.0362434679264787,
    7.1250163489017977,
    3.5763343749973511,
    1.7899106082460694,
    0.8951737102110744,
    0.4476141708605531,
    0.2238105003685381,
    0.1119056770662069,
    0.0559528918938037,
    0.0279764526170037,
    0.0139882271422650,
    0.0069941136753529,
    0.0034970568507040,
    0.0017485284269804,
    0.0008742642136938,
    0.0004371321068723,
    0.0002185660534393,
    0.0001092830267201,
    0.0000546415133601,
    0.0000273207566800,
    0.0000136603783400,
    0.0000068301891700,
    0.0000034150945850,
    0.0000017075472925,
    0.0000008537736463,
    0.0000004268868231,
    0.0000002134434116,
    0.0000001067217058,
    0.0000000533608529,
    0.0000000266804264,
    0.0000000133402132,
    0.0000000066701066,
    0.0000000033350533,
    0.0000000016675267,
    0.0000000008337633,
    0.0000000004168817,
    0.0000000002084408,
    0.0000000001042204,
    0.0000000000521102,
    0.0000000000260551,
    0.0000000000130276,
    0.0000000000065138,
    0.0000000000032569,
    0.0000000000016284,
    0.0000000000008142,
    0.0000000000004071,
    0.0000000000002036,
    0.0000000000001018,
    0.0000000000000509,
    0.0000000000000254,
    0.0000000000000127,
    0.0000000000000064,
    0.0000000000000032,
    0.0000000000000016,
    0.0000000000000008,
    0.0000000000000004,
    0.0000000000000002,
    0.0000000000000001};

  if(theta > 90){
    c.r = 0;
    c.i = 1;
    phase += 90;
  }
  else if (theta < -90){
    c.r = 0;
    c.i = -1;
    phase -= 90;
  } else {
    c.r = 1;
    c.i = 0;
  }

  for(int x = 0; x < MAX_ITER; x++){
    printf("%f\n", phase);
    print_cnum(c);
    if(theta > phase){
      c = c_mult(c,r);
      phase += atan_table[x];
    }
    else if(theta < phase){
      c = c_mult(c,c_conj(r));
      phase -= atan_table[x];
    } else {
      return c.i * (cord_mag(x)-1);
    }

    r.i /= 2;

  }

  return c.i * (cord_mag(MAX_ITER)-1);
}

void print_cnum(struct cnum c){
  printf("%f + %fi\n", c.r, c.i);
}
