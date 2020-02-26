#ifndef CORDIC_H
#define CORDIC_H

struct cnum{
  double r;
  double i;
};

struct cnum c_mult(struct cnum a, struct cnum b);
struct cnum c_conj(struct cnum c);

void print_cnum(struct cnum c);

#endif
