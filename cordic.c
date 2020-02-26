#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cordic.h"

int main(int argc, char* argv[]){
  struct cnum a = {1,2};
  struct cnum b = {2,1};

  print_cnum(c_mult(a,b));
  print_cnum(c_conj(a));
}

struct cnum c_mult(struct cnum a, struct cnum b){
  struct cnum c = {0,0};
  c.r = (a.r*b.r)-(a.i*b.i);
  c.i = (a.r*b.i)+(a.i+b.r);

  return c;
}

struct cnum c_conj(struct cnum c){
  struct cnum cf = {c.r,-c.i};
  return cf;
}

void print_cnum(struct cnum c){
  printf("%f + %fi\n", c.r, c.i);
}
