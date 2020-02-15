/**
  * @brief  二分法检索.
  */
#include <stdio.h>
#include <math.h>

#define ep 0.5e-5

double f(double x)
{
    return pow(x, 4) - 3 * x + 1;
}

double binary_search(double a, double b)
{
    double x = (a + b) / 2;
    if (f(x) == 0)
        return x;
    if (f(a) * f(x) < 0)
        b = x;
    else
        a = x;
    if (b - a < ep)
        return x;
    else
        return binary_search(a, b);
}

int main()
{
    printf("近似解：%.5lf\n", binary_search(0.3, 0.4));
    getchar();
    return 0;
}
