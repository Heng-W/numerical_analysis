/**
  * @brief  利用m次牛顿插值法计算出某一点的函数值.
  */
#include <stdio.h>


#define m 4//插值次数(m<n)
#define n 5//观测数据个数


double x[n] = { 0.25, 0.30, 0.36, 0.39, 0.45 };
double y[n] = { 0.2231436, 0.2623643, 0.3074847, 0.3293037, 0.3715636 };


double newton_interpolate(double xvalue)
{
    double form[n][n];
    double yvalue = 0, mul = 1;
    for (int i = 0; i < n; i++)    /*计算均差表*/
        form[i][0] = y[i];
    for (int j = 1; j < n; j++)
        for (int i = j; i < n; i++)
            form[i][j] = (form[i][j - 1] - form[i - 1][j - 1]) / (x[i] - x[i - j]);
    puts("观测数据构造的均差表：");
    for (int i = 0; i < n; i++, puts(""))   /*输出均差表*/
    {
        printf("%f ", x[i]);
        for (int j = 0; j < n; j++)
        {
            if (i >= j)
            {
                printf("%f ", form[i][j]);
            }
        }
    }
    for (int i = 0; i < m + 1; i++)
    {
        yvalue += form[i][i] * mul;
        mul *= (xvalue - x[i]);
    }
    return yvalue;
}


int main()
{
    double x = 0.275;
    printf("f(%g): %.10f\n", x, newton_interpolate(x));
    getchar();
    return 0;
}
