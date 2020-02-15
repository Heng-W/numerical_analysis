/**
  * @brief  利用牛顿迭代法求解非线性方程组的根.
  */
#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define n 2  //未知数个数
#define eps 0.5e-6 //精度
#define Kmax 1000  //最大迭代次数

double x[n] = { 1.0, 1.0 }; //迭代初值
int k; //迭代次数


//计算函数值
void cal_func(double* f)
{
    f[0] = pow(x[0], 2) + pow(x[1], 2) - x[0];
    f[1] = pow(x[0], 2) - pow(x[1], 2) - x[1];
}


//计算雅可比矩阵
void cal_jacobi_mat(double** df)
{
    df[0][0] = 2 * x[0] - 1;
    df[0][1] = 2 * x[1];
    df[1][0] = 2 * x[0];
    df[1][1] = -2 * x[1] - 1;
}


//高斯消元解线性方程组
double* solve_equations(double** df, double* f)
{
    double Ab[n][n + 1];    //增广矩阵
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Ab[i][j] = df[i][j];
    for (int i = 0; i < n; i++)
        Ab[i][n] = -f[i];
    double* x = NULL;
    for (int k = 0; k < n - 1; k++)     /*消元过程*/
    {
        int r = k;
        for (int i = k + 1; i < n; i++)      //按列选主元
        {
            if (fabs(Ab[i][k]) > fabs(Ab[r][k]))
            {
                r = i;
            }
        }
        if (fabs(Ab[r][k]) < eps)
        {
            return x;
        }
        if (r > k)              //行交换
        {
            double tmp;
            for (int j = 0; j < n + 1; j++)
            {
                tmp = Ab[k][j];
                Ab[k][j] = Ab[r][j];
                Ab[r][j] = tmp;
            }
        }
        for (int i = k + 1; i < n; i++)     //消元计算,化为上三角
        {
            double radio = Ab[i][k] / Ab[k][k];
            for (int j = k; j < n + 1; j++)
            {
                Ab[i][j] -= radio * Ab[k][j];
            }
        }
    }
    if (fabs(Ab[n - 1][n - 1]) < eps)   /*回代过程*/
    {
        return x;
    }
    x = (double*)malloc(n * sizeof(double));
    for (int k = n - 1; k >= 0; k--)
    {
        double sum = 0;
        for (int j = k + 1; j < n; j++)
        {
            sum += Ab[k][j] * x[j];
        }
        x[k] = (Ab[k][n] - sum) / Ab[k][k];
    }
    return x;
}


//牛顿迭代解非线性方程组
void newton_iterate()
{
    int exitFlag = 0;
    double* f = (double*)malloc(n * sizeof(double));
    double** df = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
    {
        df[i] = (double*)malloc(n * sizeof(double));
    }
    while (!exitFlag)
    {
        k++;
        cal_jacobi_mat(df);
        cal_func(f);
        double* delta = solve_equations(df, f);
        if (delta == NULL || k > Kmax)
        {
            printf("迭代失败\n");
            break;
        }
        exitFlag = 1;
        for (int i = 0; i < n; i++)
        {
            x[i] += delta[i];
            if (fabs(delta[i]) > eps)
            {
                exitFlag = 0;
            }
        }
        free(delta);
    }
    free(f);
    for (int i = 0; i < n; i++)
    {
        free(df[i]);
    }
    free(df);
}


int main()
{
    newton_iterate();
    for (int i = 0; i < n; i++)
    {
        printf("X%d=%f  ", i + 1, x[i]);
    }
    printf("\n迭代次数：%d\n", k);
    getchar();
    return 0;
}