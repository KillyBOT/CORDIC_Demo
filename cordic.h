#ifndef CORDIC_H
#define CORDIC_H

struct cnum{
  double r;
  double i;
};

struct cnum c_mult(struct cnum a, struct cnum b); //Multiply two complex numbers
struct cnum c_conj(struct cnum c); //Get the conjugate of a complex number
double c_mag(struct cnum c); //Find the magnitude of a complex number
double c_phase(struct cnum c); //Find the phase (angle) of a complex number

double cord_mag(); //Just to test the exact value of the CORDIC gain


void print_cnum(struct cnum c);

#endif
