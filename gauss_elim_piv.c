/**
  * @brief  利用列主元高斯消元法，把线性方程组化为下三角
线性方程组，然后求解下三角线性方程组来得到原方程组的解.
  */
#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define n  4              //未知数个数
#define eps 0.5e-6        //精度


double A[n][n] = { {5, 7, 9, 10}, {6, 8, 10, 9}, {7, 10, 8, 7}, {5, 7, 6, 5} }; //系数矩阵A
double b[n] = { 1, 1, 1, 1 }; //矩阵b


double* gauss_elim_piv(double (*A)[n], double* b)
{
    double* x = NULL;
    double Ab[n][n + 1];    //增广矩阵
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Ab[i][j] = A[i][j];
    for (int i = 0; i < n; i++)
        Ab[i][n] = b[i];
    for (int k = n - 1; k > 0; k--)     /*消元过程*/
    {
        int r = k;
        for (int i = 0; i < k; i++)     //选列主元
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
        if (r < k)                  //行交换
        {
            double tmp;
            for (int j = 0; j < n + 1; j++)
            {
                tmp = Ab[k][j];
                Ab[k][j] = Ab[r][j];
                Ab[r][j] = tmp;
            }
        }
        for (int i = 0; i < k; i++)         //消元计算
        {
            double ratio = Ab[i][k] / Ab[k][k];
            for (int j = 0; j < n + 1; j++)
            {
                Ab[i][j] -= ratio * Ab[k][j];
            }
        }
    }
    for (int i = 0; i < n; i++, puts(""))   //输出下三角矩阵
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f ", Ab[i][j]);
        }
    }
    puts("");
    if (fabs(Ab[0][0]) < eps)           /*回代过程*/
    {
        return x;
    }
    x = (double*)malloc(n * sizeof(double));
    for (int k = 0; k < n; k++)
    {
        double sum = 0;
        for (int j = 0; j < k; j++)
        {
            sum += Ab[k][j] * x[j];
        }
        x[k] = (Ab[k][n] - sum) / Ab[k][k];
    }
    return x;
}


int main()
{
    double* x = gauss_elim_piv(A, b);
    if (x == NULL)
    {
        printf("系数矩阵奇异\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        printf("X%d: %f  ", i + 1, x[i]);
    }
    free(x);
    puts("");
    getchar();
    return 0;
}