/**
  * @brief  利用平方根法求解线性方程组的根.
  */
#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define n 3

double A[n][n] = { {4, 2, -2}, {2, 2, -3}, {-2, -3, 14} };
double b[n] = { 10, 5, 4 };


double* cholesky()
{
    double L[n][n];
    for (int k = 0; k < n; k++)     /*分解A得到A=L*L^T*/
    {
        double sum = 0;
        for (int i = 0; i < k; i++)
            sum += L[k][i] * L[k][i];
        sum = A[k][k] - sum;
        L[k][k] = sqrt(sum > 0 ? sum : 0);
        for (int i = k + 1; i < n; i++)
        {
            sum = 0;
            for (int j = 0; j < k; j++)
                sum += L[i][j] * L[k][j];
            L[i][k] = (A[i][k] - sum) / L[k][k];
        }
        for (int j = 0; j < k; j++)
        {
            L[j][k] = 0;
        }
    }
    for (int i = 0; i < n; i++, puts(""))
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f  ", L[i][j]);
        }
    }
    /*回代过程*/
    double* x = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
        x[i] = b[i];
    for (int k = 0; k < n; k++)     /*LY=b ,solve Y*/
    {
        for (int i = 0; i < k; i++)
            x[k] -= x[i] * L[k][i];
        x[k] /= L[k][k];
    }
    for (int k = n - 1; k >= 0; k--)    /*L^TX=Y,solve X*/
    {
        for (int i = k + 1; i < n; i++)
            x[k] -= x[i] * L[i][k];
        x[k] /= L[k][k];
    }
    return x;
}

int main()
{
    double* x = cholesky();
    for (int i = 0; i < n; i++)
    {
        printf("X%d:%f ", i + 1, x[i]);
    }
    free(x);
    puts("");
    getchar();
    return 0;
}
