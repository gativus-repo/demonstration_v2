#include <stdio.h>

int calculate_roots();

int main (){
  double a = 1, b=4, c=-12;
  double x1,x2;
  
  int num_roots = calculate_roots(a, b, c, &x1, &x2);
  
  switch (num_roots) {
    case 0:
      printf("0 R-space roots, %.2f \n", x1);
      break;
    case 1:
      printf("1 root: %.2f\n", x1);
      break;
    case 2:
      printf("2 roots: %.2f, %.2f \n", x1,x2);
      break;
    return 0;
  }
}

