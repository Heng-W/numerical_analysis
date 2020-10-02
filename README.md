# numerical_analysis

### Common numerical analysis algorithm. 
### 数值分析常用算法


- 方程求根：二分法(binary_search.c)、牛顿迭代法(newton_iter.c)
- 函数拟合：最小二乘法(ls_fit.c)、样条插值法(spline.c)、牛顿插值法(newton_interpolate.c)
- 线性方程组求解：SOR迭代法(sor.c)、列主元高斯消元法(gauss_elim_piv.c)、平方根法(sqrt_method.c)
- 非线性方程组求解：牛顿迭代法（newton_iters.c）


### 生成所有可执行文件：

-Windows平台安装gcc编译器后，双击compile.bat或输入make -f Makefile.win.mk
-Linux平台直接make