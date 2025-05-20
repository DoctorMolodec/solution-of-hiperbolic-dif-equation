#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "interpolation2.h"
#include "method2_1.h"

//interpolation in three-dimensional space
static double f0(double x)
{
    return x * 0 + 1;
}
static double f1(double x)
{
    return x*0;
}
static double f2(double x)
{
    return cos(x);
}
static double f3(double x)
{
    return x;
}
static double f4(double x)
{
    return sqrt(fabs(x));
}
static double f5(double x)
{
    return x * x;
}
static double f6(double x)
{
    return exp(x);
}
static double f7(double x)
{
    return 1 / (25 * x * x + 1);
}

interpolation2_ctx interpolation2_create(
    int n_x, int n_y, int k, int k1, int k2, double nu,
    double x_a, double x_b, double y_a, double y_b)
{
    //verification of the obtained data validity
    interpolation2_ctx res_ptr;
    if (n_x < 3 || n_y < 3 || x_a >= x_b || y_a >= y_b)
    {
        return NULL;
    }

    res_ptr = (interpolation2_ctx)malloc(sizeof(*res_ptr));
    if (res_ptr == NULL)
    {
        return NULL;
    }

    res_ptr->k = k;
    res_ptr->k1 = k1;
    res_ptr->k2 = k2;
    res_ptr->nu = nu;
    res_ptr->n_x = n_x;
    res_ptr->x_a = x_a;
    res_ptr->x_b = x_b;
    res_ptr->n_y = n_y;
    res_ptr->y_a = y_a;
    res_ptr->y_b = y_b;
    res_ptr->h_x = (res_ptr->x_b - res_ptr->x_a) / (res_ptr->n_x - 1);
    res_ptr->h_y = (res_ptr->y_b - res_ptr->y_a) / (res_ptr->n_y - 1);
    res_ptr->G = (double*)malloc(( n_x * n_y) * sizeof(double));
    if (res_ptr->G == NULL)
    {
        free(res_ptr->G);
        free(res_ptr);
        return NULL;
    }
    switch (k)
    {
    case INTERPOLATION2_F_1:
        res_ptr->f = f0;
        break;
    case INTERPOLATION2_F_X:
        res_ptr->f = f1;
        break;
    case INTERPOLATION2_F_Y:
        res_ptr->f = f2;
        break;
    case INTERPOLATION2_F_XY:
        res_ptr->f = f3;
        break;
    case INTERPOLATION2_F_SQRX2Y2:
        res_ptr->f = f4;
        break;
    case INTERPOLATION2_F_X2Y2:
        res_ptr->f = f5;
        break;
    case INTERPOLATION2_F_EX2Y2:
        res_ptr->f = f6;
        break;
    case INTERPOLATION2_F_1DIVX2Y2:
        res_ptr->f = f7;
        break;
    default:
        free(res_ptr->G);
        free(res_ptr);
        return NULL;
    }
    
    switch (k1)
    {
    case INTERPOLATION2_F_1:
        res_ptr->f1 = f0;
        break;
    case INTERPOLATION2_F_X:
        res_ptr->f1 = f1;
        break;
    case INTERPOLATION2_F_Y:
        res_ptr->f1 = f2;
        break;
    case INTERPOLATION2_F_XY:
        res_ptr->f1 = f3;
        break;
    case INTERPOLATION2_F_SQRX2Y2:
        res_ptr->f = f4;
        break;
    case INTERPOLATION2_F_X2Y2:
        res_ptr->f1 = f5;
        break;
    case INTERPOLATION2_F_EX2Y2:
        res_ptr->f1 = f6;
        break;
    case INTERPOLATION2_F_1DIVX2Y2:
        res_ptr->f1 = f7;
        break;
    default:
        free(res_ptr->G);
        free(res_ptr);
        return NULL;
    }

    switch (k2)
    {
    case INTERPOLATION2_F_1:
        res_ptr->f2 = f0;
        break;
    case INTERPOLATION2_F_X:
        res_ptr->f2 = f1;
        break;
    case INTERPOLATION2_F_Y:
        res_ptr->f2 = f2;
        break;
    case INTERPOLATION2_F_XY:
        res_ptr->f2 = f3;
        break;
    case INTERPOLATION2_F_SQRX2Y2:
        res_ptr->f2 = f4;
        break;
    case INTERPOLATION2_F_X2Y2:
        res_ptr->f2 = f5;
        break;
    case INTERPOLATION2_F_EX2Y2:
        res_ptr->f2 = f6;
        break;
    case INTERPOLATION2_F_1DIVX2Y2:
        res_ptr->f2 = f7;
        break;
    default:
        free(res_ptr->G);
        free(res_ptr);
        return NULL;
    }

    interpolation2_method_1(res_ptr);


    return res_ptr;
}


//here we determine which polynomial the point belongs to and calculate its value
double interpolation2_calculate(interpolation2_ctx ctx, double x, double y)
{
    int i, j;
    double res = 0;
    i = (int)((x - ctx->x_a) / ctx->h_x);
    j = (int)((y - ctx->y_a) / ctx->h_y);
    if (i < 0)
    {
        i = 0;
    }
    if (i > ctx->n_x - 2)
    {
        i = ctx->n_x - 2;
    }
    if (j < 0)
    {
        j = 0;
    }
    if (j > ctx->n_y - 2)
    {
        j = ctx->n_y - 2;
    }

    res = ctx->G[i * ctx->n_y + j];


    return res;
}

void interpolation2_destroy(interpolation2_ctx ctx)
{
    free(ctx->G);
    free(ctx);
}
