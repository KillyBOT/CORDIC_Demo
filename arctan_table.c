#include "cordic.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  int iter = 60;
  double theta = 1;
  double toDegrees = (180 / M_PI);
  FILE* fp;

  fp = fopen("atan_table","w");

  fprintf(fp, "%d\n", iter);

  for(int x = 0; x < iter; x++){
    fprintf(fp, "%.16f\n", atan(theta) * toDegrees);
    theta /= 2;
  }

  fclose(fp);

  return 0;
}
