/**
  * @brief  利用SOR迭代法求解线性方程组的根.
  */
#include <stdio.h>
#include <math.h>


#define n  6//未知数个数
#define w  1.1 //松弛因子
#define ep 1.0e-13//精度
#define N  5000//最大迭代次数

#define MAX(a,b) (((a)>(b))?(a):(b))


double a[n][n] = { {4, -1, 0, -1, 0, 0}, {-1, 4, -1, 0, -1, 0}, {0, -1, 4, 0, 0, -1},
    {-1, 0, 0, 4, -1, 0}, {0, -1, 0, -1, 4, -1}, {0, 0, 1, 0, -1, 4}
};
double b[n] = { 2, 3, 2, 2, 1, 2 };

double x[n];
int k;

void sor_iterate()
{
    double norm;
    while (1)
    {
        if (++k > N)
        {
            printf("迭代失败\n");
            break;
        }
        norm = 0;
        for (int i = 0; i < n; i++)
        {
            double sum = 0;
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                    sum += a[i][j] * x[j];
            }
            double s = x[i];
            x[i] = (1 - w) * x[i] + w / a[i][i] * (b[i] - sum);
            norm = MAX(norm, fabs(s - x[i]));
        }
        if (norm < ep)
        {
            break;
        }
    }
}

int main()
{
    sor_iterate();
    puts("近似解:");
    for (int i = 0; i < n; i++)
    {
        printf("%.3lf ", x[i]);
    }
    puts("");
    printf("\n迭代次数：%d\n", k);
    getchar();
    return 0;
}