#include "method2_1.h"

double F(interpolation2_ctx ctx, double u, int i, int j)
{
    if (u >= 0)
    {
        return ctx->G[(i + 1) * ctx->n_y + j - 1] - ctx->G[(i)*ctx->n_y + j - 1];
    }
    else
    {
        return ctx->G[(i) * ctx->n_y + j - 1] - ctx->G[(i-1)*ctx->n_y + j - 1];
    }

}


void interpolation2_method_1(interpolation2_ctx ctx)
{
    double a = ctx->h_y / ctx->h_x;
    double b = a/ ctx->h_x * ctx->nu;
    for (int i = 0; i < ctx->n_x; i++)
    {
        ctx->G[i * ctx->n_y] = ctx->f(i * ctx->h_x);
    }
    for (int j = 1; j < ctx->n_y; j++)
    {
        ctx->G[0 * ctx->n_y + j] = ctx->f2(j*ctx->h_y);
        ctx->G[(ctx->n_x - 1) * ctx->n_y + j] = ctx->f1(j*ctx->h_y);
    }
    for (int j = 1; j < ctx->n_y; j++)
    {
        for (int i = 1; i < ctx->n_x - 1; i++)
        {
            ctx->G[i*ctx->n_y+j] = ctx->G[i * ctx->n_y + j-1] + 
                a * F(ctx, ctx->G[i * ctx->n_y + j - 1], i, j)  * ctx->G[i * ctx->n_y + j - 1]
                + b * (ctx->G[(i - 1) * ctx->n_y + j-1] - 2 * ctx->G[i * ctx->n_y + j-1]
                    + ctx->G[(i + 1) * ctx->n_y + j-1]);
        }
    }
}



