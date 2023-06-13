#include <math.h>
#include <stdio.h>

int main() {
    double x, ret;
    x = 2.7;

    ret = log(x);
    printf("ln(%lf)  = %lf\n", x, ret);
    printf("ln(1.0) = %lf\n", log(1.0));
    printf("ln(2.0) = %lf\n", log(2.0));
    printf("ln(200.0) = %lf\n", log(200.0));

    printf("ln(200.0) / ln(2.0) = %lf\n", log(200.0) / log(2.0));

    return 0;
}
