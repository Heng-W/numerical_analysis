/**
  * @brief  牛顿迭代法求根.
  */
#include <stdio.h>
#include <math.h>

#define ep 0.5e-5

double f(double x)
{
    return pow(x, 3) - 3 * x - 1;
}

double df(double x)
{
    return 3 * pow(x, 2) - 3;
}

double newton_solve(double x)
{
    while (1)
    {
        double x1 = x - f(x) / df(x);
        if (fabs(x1 - x) < ep)
            return x1;
        else
            return newton_solve(x1);
    }
}

int main()
{
    printf("%.5f", newton_solve(2));
    puts("");
    getchar();
    return 0;
}
