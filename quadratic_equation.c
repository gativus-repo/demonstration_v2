#include <math.h>

double calculate_discriminant (double a, double b, double c);

void calculate_roots (double a, double b, double c, double *x1, double *x2, int *flag, double *D) {
    *D = calculate_discriminant(a,b,c);
    
    if (*D < 0){
      *flag = 0;
    } else if (*D == 0){
      *x1 = -b / (2 * a);
      *flag = 1;
    } else if (*D > 0){
      *x1 = (-b - sqrt(*D)) / (2 * a);
      *x2 = (-b + sqrt(*D)) / (2 * a);
      *flag = 2;
    }
}
