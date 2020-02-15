/**
  * @brief  N次样条插值法拟合一元多次函数表达式.
  */
#include <stdio.h>
#include <malloc.h>
#include <math.h>


#define N  3//插值次数
#define n  4 * N
#define ep 1.0e-5

double x[N + 1] = { 0, 1, 2, 3 };
double y[N + 1] = { 0, 0, 1, 0 };

double gz[4 * N][4 * N + 1];


void init_matrix()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gz[i][4 * i + j] = pow(x[i], 3 - j);
        }
    }
    for (int j = 0; j < 4; j++)
    {
        gz[N][4 * (N - 1) + j] = pow(x[N], 3 - j);
    }
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gz[i + N + 1][4 * i + j] = pow(x[i + 1], 3 - j);
            gz[i + N + 1][4 * i + 4 + j] = -pow(x[i + 1], 3 - j);
            gz[i + 2 * N][4 * i + j] = (3 - j) * pow(x[i + 1], 2 - j);
            gz[i + 2 * N][4 * i + 4 + j] = -(3 - j) * pow(x[i + 1], 2 - j);
        }
    }
    for (int i = 0; i < N - 1; i++)
    {
        gz[i + 3 * N - 1][4 * i] = 6 * x[i + 1];
        gz[i + 3 * N - 1][4 * i + 1] = 2;
    }
    /*gz[4 * N - 2][0] = 0;
    gz[4 * N - 2][1] = 2;
    gz[4 * N - 1][4 * N - 4] = 6 * 3;
    gz[4 * N - 1][4 * N - 3] = 2;*/
    gz[4 * N - 2][0] = 0;
    gz[4 * N - 2][1] = 0;
    gz[4 * N - 2][2] = 1;
    gz[4 * N - 1][4 * N - 4] = 3 * 9;
    gz[4 * N - 1][4 * N - 3] = 2 * 3;
    gz[4 * N - 1][4 * N - 2] = 1;
    for (int i = 0; i < N + 1; i++)
    {
        gz[i][4 * N] = y[i];
    }
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
    for (int i = 0; i < N; i++, puts(""))
    {
        printf("y = %.2f x^3 + %.2f x^2 + %.2f x + %.2f", x[4 * i], x[4 * i + 1], x[4 * i + 2], x[4 * i + 3]);
    }
    free(x);
    getchar();
    return 0;
}