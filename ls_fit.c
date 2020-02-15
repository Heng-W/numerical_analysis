/**
  * @brief 根据观测点用最小二乘法拟合一元多次函数表达式.
  */
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <math.h>

#define N  7//观测点数量
#define M  1//拟合次数
#define ep 1.0e-13

#define n  (M + 1)

double x[N] = { 1, 2, 4, 8, 16, 32, 64 };
double y[N] = { 4.22, 4.02, 3.85, 3.59, 3.44, 3.02, 2.59 };

double gm[N][M + 2];//增广矩阵(矛盾方程组)
double gz[M + 1][M + 2];//增广矩阵(正规方程组)

void init_matrix()
{
    for (int i = 0; i < N; i++)
    {
        x[i] = log(x[i]);
        y[i] = log(y[i]);
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M + 2; j++)
            if (j == M + 1)
                gm[i][j] = y[i];
            else
                gm[i][j] = pow(x[i], j);
    for (int i = 0; i < M + 1; i++)
        for (int j = 0; j < M + 2; j++)
            for (int k = 0; k < N; k++)
                gz[i][j] += gm[k][i] * gm[k][j];
}

double* solve_equations(double(*g)[n + 1])
{
    int r;
    double* x = NULL;
    /*消元过程*/
    for (int k = 0; k < n - 1; k++)
    {
        //按列选主元
        r = k;
        for (int i = k + 1; i < n; i++)
        {
            if (fabs(g[i][k]) > fabs(g[r][k]))
            {
                r = i;
            }
        }
        if (fabs(g[r][k]) < ep)
        {
            printf("系数矩阵奇异\n");
            return x;
        }
        //行交换
        if (r > k)
        {
            double tmp;
            for (int j = 0; j < n + 1; j++)
            {
                tmp = g[k][j];
                g[k][j] = g[r][j];
                g[r][j] = tmp;
            }
        }
        //消元计算
        for (int i = k + 1; i < n; i++)
        {
            double rate = g[i][k] / g[k][k];
            for (int j = k; j < n + 1; j++)
            {
                g[i][j] -= rate * g[k][j];
            }
        }
    }
    /*回代过程*/
    if (fabs(g[n - 1][n - 1]) < ep)
    {
        printf("系数矩阵奇异\n");
        return x;
    }
    else
    {
        x = (double*)malloc(n * sizeof(double));
        for (int k = n - 1; k >= 0; k--)
        {
            double sum = 0;
            for (int j = k + 1; j < n; j++)
            {
                sum += g[k][j] * x[j];
            }
            x[k] = (g[k][n] - sum) / g[k][k];
        }
    }
    return x;
}


int main()
{
    init_matrix();
    double* x = solve_equations(gz);
    double r = x[1];
    double c = exp(x[0]);
    puts("系数值");
    printf("c=%.2f,r=%.2f\n", c, r);
    free(x);
    getchar();
    return 0;
}