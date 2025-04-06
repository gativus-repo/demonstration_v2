#include <gtk/gtk.h>

gdouble calculate_discriminant (gdouble a, gdouble b, gdouble c) {
    return (b*b - (4 * a * c));
}

void calculate_roots (gdouble a, gdouble b, gdouble c, gdouble *x1, gdouble *x2, gint *flag, gdouble *D) {
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
