/*
Name: geofindkey2p.c
Version: 2.7
Date: 2021-11-22
Author: zvezdochiot (https://github.com/zvezdochiot)
*
build:
$ gcc -o geofindkey2p geofindkey2p.c -lm
sample:
$ ./geofindkey2p doc/data.dat report.dat
*
file:
input file doc/data.dat:
*
1 1334.71   285.94 66.29 83477.64 47377.60 216.28 1.0
2  563.67 -5197.34 60.21 82557.14 41916.51 210.21 1.0
3 4444.27  1153.79 67.76 86610.19 48160.39 217.77 1.0
4 -252.07  2881.90 65.41 81962.05 50016.34 215.42 1.0
5 1334.71   285.94 66.29
6  563.67 -5197.34 60.21
7 4444.27  1153.79 67.76
8 -252.07  2881.90 65.41
*
output file report.dat:
*
key:
--0-----
82135.4060
47128.1486
150.3057
--1-----
0.999791518237
-0.027293637599
0.989847192109
--2-----
-0.000000001537
0.000000000324
0.000084448305
========
1.000163997848
-1.5637479503

var:
1 1334.7100 285.9400 66.2900 83477.6400 47377.6000 216.2800 1 -0.0007 -0.0007 +0.0138
2 563.6700 -5197.3400 60.2100 82557.1400 41916.5100 210.2100 1 +0.0072 -0.0021 +0.0006
3 4444.2700 1153.7900 67.7600 86610.1900 48160.3900 217.7700 1 +0.0190 -0.0020 -0.0045
4 -252.0700 2881.9000 65.4100 81962.0500 50016.3400 215.4200 1 +0.0093 -0.0127 -0.0071
5 1334.7100 285.9400 66.2900 83477.6393 47377.5993 216.2938
6 563.6700 -5197.3400 60.2100 82557.1472 41916.5079 210.2106
7 4444.2700 1153.7900 67.7600 86610.2090 48160.3880 217.7655
8 -252.0700 2881.9000 65.4100 81962.0593 50016.3273 215.4129

diff:
0.0158 0.0092 0.0114
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define PNAME "GeoFindKey2Pow"
#define PVERSION "2.7"

void geofindkey2ptitle()
{
    fprintf(stderr, "%s %s\n", PNAME, PVERSION);
}

void geofindkey2pusage()
{
    fprintf(stderr, "usage: geofindkey2p [option] input-file report-file\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "          -d N    decimal after comma, default=4\n");
    fprintf(stderr, "          -h      this help\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "input-file(sample):\n");
    fprintf(stderr, " 1 1334.71   285.94 66.29 83477.64 47377.60 216.28 1.0\n");
    fprintf(stderr, " 2  563.67 -5197.34 60.21 82557.14 41916.51 210.21 1.0\n");
    fprintf(stderr, " 3 4444.27  1153.79 67.76 86610.19 48160.39 217.77 1.0\n");
    fprintf(stderr, " 4 -252.07  2881.90 65.41 81962.05 50016.34 215.42 1.0\n");
    fprintf(stderr, " 5 1334.71   285.94 66.29\n");
    fprintf(stderr, " 6  563.67 -5197.34 60.21\n");
    fprintf(stderr, " 7 4444.27  1153.79 67.76\n");
    fprintf(stderr, " 8 -252.07  2881.90 65.41\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "report-file(sample):\n");
    fprintf(stderr, " key:\n");
    fprintf(stderr, " --0-----\n");
    fprintf(stderr, " 82135.4060\n");
    fprintf(stderr, " 47128.1486\n");
    fprintf(stderr, " 150.3057\n");
    fprintf(stderr, " --1-----\n");
    fprintf(stderr, " 0.999791518237\n");
    fprintf(stderr, " -0.027293637599\n");
    fprintf(stderr, " 0.989847192109\n");
    fprintf(stderr, " --2-----\n");
    fprintf(stderr, " -0.000000001537\n");
    fprintf(stderr, " 0.000000000324\n");
    fprintf(stderr, " 0.000084448305\n");
    fprintf(stderr, " ========\n");
    fprintf(stderr, " 1.000163997848\n");
    fprintf(stderr, " -1.5637479503\n");
    fprintf(stderr, " \n");
    fprintf(stderr, " var:\n");
    fprintf(stderr, " 1 1334.7100 285.9400 66.2900 83477.6400 47377.6000 216.2800 1 -0.0007 -0.0007 +0.0138\n");
    fprintf(stderr, " 2 563.6700 -5197.3400 60.2100 82557.1400 41916.5100 210.2100 1 +0.0072 -0.0021 +0.0006\n");
    fprintf(stderr, " 3 4444.2700 1153.7900 67.7600 86610.1900 48160.3900 217.7700 1 +0.0190 -0.0020 -0.0045\n");
    fprintf(stderr, " 4 -252.0700 2881.9000 65.4100 81962.0500 50016.3400 215.4200 1 +0.0093 -0.0127 -0.0071\n");
    fprintf(stderr, " 5 1334.7100 285.9400 66.2900 83477.6393 47377.5993 216.2938\n");
    fprintf(stderr, " 6 563.6700 -5197.3400 60.2100 82557.1472 41916.5079 210.2106\n");
    fprintf(stderr, " 7 4444.2700 1153.7900 67.7600 86610.2090 48160.3880 217.7655\n");
    fprintf(stderr, " 8 -252.0700 2881.9000 65.4100 81962.0593 50016.3273 215.4129\n");
    fprintf(stderr, " \n");
    fprintf(stderr, " diff:");
    fprintf(stderr, " 0.0158 0.0092 0.0114");
}

int main(int argc, char *argv[])
{
    char buf[1024], name[32], format3[128], format7[128], format11[128];
    double x[3] = {0}, y[3] = {0}, z[3] = {0}, wgt, n;
    double xc[4] = {0}, yc[4] = {0};
    double dx[3] = {0}, dy[3] = {0}, dzs[3] = {0};
    double a[3][3], scale, rotation;
    double tx, ty, tx2, ty2;
    double s[21] = {0};
    int i, np;
    FILE *fp0, *fp1;

    int opt;
    int decimals = 4;   /* number of decimals in the calculated coordinates */
    int fhelp = 0;
    while ((opt = getopt(argc, argv, "d:h")) != -1)
    {
        switch(opt)
        {
        case 'd':
            decimals = atoi(optarg);
            break;
        case 'h':
            fhelp = 1;
            break;
        case ':':
            fprintf(stderr, "option needs a value\n");
            break;
        case '?':
            fprintf(stderr, "unknown option: %c\n", optopt);
            break;
        }
    }

    sprintf(format3, "%%.%df %%.%df %%.%df\n",
            decimals, decimals, decimals);
    sprintf(format7, "%%s %%.%df %%.%df %%.%df %%.%df %%.%df %%.%df\n",
            decimals, decimals, decimals, decimals, decimals, decimals);
    sprintf(format11, "%%s %%.%df %%.%df %%.%df %%.%df %%.%df %%.%df %%g %%+.%df %%+.%df %%+.%df\n",
            decimals, decimals, decimals, decimals, decimals, decimals, decimals, decimals, decimals);
    geofindkey2ptitle();

    if ((optind + 2 > argc) || (fhelp > 0))
    {
        geofindkey2pusage();
        exit(0);
    }

    if ((fp0 = fopen(argv[optind], "r")) == NULL)
    {
        fprintf(stderr, "can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* подсчитать сумму координат */
    n = 0.0;
    for (i = 0; i < 21; i++)
    {
        s[i] = 0.0;
    }
    while (fgets(buf, 1024, fp0) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf %lf", name, &x[0], &x[1], &x[2], &y[0], &y[1], &y[2], &wgt);
        if (np >= 8)
        {
            s[0] += x[0] * wgt;
            s[1] += x[1] * wgt;
            s[2] += x[2] * wgt;
            s[3] += y[0] * wgt;
            s[4] += y[1] * wgt;
            s[5] += y[2] * wgt;
            s[6] += wgt;
            n++;
            xc[3] += (x[0] * x[0] + x[1] * x[1]) * wgt;
            yc[3] += (x[2] * x[2]) * wgt;
        }
    }
    n = (s[6] > 0.0) ? s[6] : n;
    if (n > 0.0)
    {
        xc[3] -= (s[0] * s[0] + s[1] * s[1] )/ n;
        xc[3] *= 2.0;
        xc[3] /= n;
        xc[3] = (xc[3] > 0.0) ? (1.0 / sqrt(xc[3])) : 1.0;
        yc[3] -= (s[2] * s[2])/ n;
        yc[3] *= 2.0;
        yc[3] /= n;
        yc[3] = (yc[3] > 0.0) ? (1.0 / sqrt(yc[3])) : 1.0;
    }
    else
    {
        xc[3] = 1.0;
        yc[3] = 1.0;
    }

    rewind(fp0);

    /* найти центр масс */
    for (i = 0; i < 3; i++)
    {
        xc[i] = s[i];
        yc[i] = s[3 + i];
        if (n > 0.0)
        {
            xc[i] /= n;
            yc[i] /= n;
        }
    }

    /* подсчитать сумму произведений */
    for (i = 0; i < 21; i++)
    {
        s[i] = 0.0;
    }
    while (fgets(buf, 1024, fp0) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf %lf", name, &x[0], &x[1], &x[2], &y[0], &y[1], &y[2], &wgt);
        if (np >= 8)
        {
            /* вычислить разности */
            for (i = 0; i < 3; i++)
            {
                dx[i] = (x[i] - xc[i]);
                dy[i] = (y[i] - yc[i]);
            }
            dx[0] *= xc[3];
            dx[1] *= xc[3];
            dx[2] *= yc[3];
            tx = dx[0];
            ty = dx[1];
            tx2 = tx * tx;
            ty2 = ty * ty;
            /* суммировать */
            s[0] += (tx2 + ty2) * wgt;
            s[1] += (tx2 * tx + tx * ty2) * wgt;
            s[2] += (ty2 * ty + tx2 * ty) * wgt;
            s[3] += (tx2 + ty2) * (tx2 + ty2) * wgt;
            s[4] += (dy[0] * tx + dy[1] * ty) * wgt;
            s[5] += (dy[1] * tx - dy[0] * ty) * wgt;
            s[6] += (dy[0] * tx2 - dy[0] * ty2 + 2 * dy[1] * tx * ty) * wgt;
            s[7] += (dy[1] * tx2 - dy[1] * ty2 - 2 * dy[0] * tx * ty) * wgt;
            s[8] += dx[2] * dx[2] * wgt;
            s[9] += dx[2] * dx[2] * dx[2] * wgt;
            s[10] += dx[2] * dx[2] * dx[2] * dx[2] * wgt;
            s[11] += dx[2] * dy[2] * wgt;
            s[12] += dx[2] * dx[2] * dy[2] * wgt;
        }
    }
    s[13] = s[1] * s[6] - s[2] * s[7] - s[3] * s[4];
    s[14] = s[1] * s[7] + s[2] * s[6] - s[3] * s[5];
    s[15] = s[1] * s[4] + s[2] * s[5] - s[0] * s[6];
    s[16] = s[1] * s[5] - s[2] * s[4] - s[0] * s[7];
    s[17] = s[1] * s[1] + s[2] * s[2] - s[0] * s[3];
    s[18] = s[13] * (s[9] * s[12] - s[10] * s[11]) + s[8] * s[8] * s[11];
    s[19] = s[13] * (s[9] * s[11] - s[8] * s[12]);
    s[20] = s[8] * s[8] * s[8] + s[13] * (s[9] * s[9] - s[8] * s[10]);
    s[13] *= xc[3];
    s[14] *= xc[3];
    s[15] *= xc[3];
    s[16] *= xc[3];
    s[15] *= xc[3];
    s[16] *= xc[3];
    s[18] *= yc[3];
    s[19] *= yc[3];
    s[19] *= yc[3];

    rewind(fp0);

    /* найти первичные параметры */
    if (s[17] < 0.0 || s[17] > 0.0)
    {
        a[1][0] = s[13] / s[17];
        a[1][1] = s[14] / s[17];
        a[2][0] = s[15] / s[17];
        a[2][1] = s[16] / s[17];
    }
    else
    {
        a[1][0] = 1.0;
        a[1][1] = 0.0;
        a[2][0] = 0.0;
        a[2][1] = 0.0;
    }
    if (s[20] < 0.0 || s[20] > 0.0)
    {
        a[2][2] = s[19] / s[20];
        a[1][2] = s[18] / s[20];
        a[1][2] -= (2.0 * a[2][2] * xc[2]);
    }
    else
    {
        a[1][2] = 1.0;
        a[2][2] = 0.0;
    }
    tx = a[1][0] - 2.0 * (a[2][0] * xc[0] - a[2][1] * xc[1]);
    ty = a[1][1] - 2.0 * (a[2][0] * xc[1] + a[2][1] * xc[0]);
    a[1][0] = tx;
    a[1][1] = ty;
    tx = xc[0] * xc[0] - xc[1] * xc[1];
    ty = xc[0] * xc[1];
    a[0][0] = yc[0] - a[1][0] * xc[0] + a[1][1] * xc[1] - a[2][0] * tx + 2 * a[2][1] * ty;
    a[0][1] = yc[1] - a[1][1] * xc[0] - a[1][0] * xc[1] - a[2][1] * tx - 2 * a[2][0] * ty;
    a[0][2] = yc[2] - (a[1][2] + a[2][2] * xc[2]) * xc[2];

    /* найти вторичные параметры */
    scale = hypot(a[1][0], a[1][1]);
    rotation = atan2(a[1][1], a[1][0]);

    /* вывести параметры в файл ключа */
    if ((fp1 = fopen(argv[optind + 1], "w")) == NULL)
    {
        fprintf(stderr, "can't create %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    fprintf(fp1, "key:\n");
    fprintf(fp1, "--0-----\n");
    fprintf(fp1, "%.4f\n", a[0][0]);
    fprintf(fp1, "%.4f\n", a[0][1]);
    fprintf(fp1, "%.4f\n", a[0][2]);
    fprintf(fp1, "--1-----\n");
    fprintf(fp1, "%.12f\n", a[1][0]);
    fprintf(fp1, "%.12f\n", a[1][1]);
    fprintf(fp1, "%.12f\n", a[1][2]);
    fprintf(fp1, "--2-----\n");
    fprintf(fp1, "%.12f\n", a[2][0]);
    fprintf(fp1, "%.12f\n", a[2][1]);
    fprintf(fp1, "%.12f\n", a[2][2]);
    fprintf(fp1, "========\n");
    fprintf(fp1, "%.12f\n", scale);
    fprintf(fp1, "%+.10f\n", rotation * 180.0 / M_PI);
    fprintf(fp1, "\n");

    /* вывести данные вместе с невязками */
    fprintf(fp1, "var:\n");
    for (i = 0; i < 21; i++)
    {
        s[i] = 0.0;
    }
    while (fgets(buf, 1024, fp0) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf %lf", name, &x[0], &x[1], &x[2], &y[0], &y[1], &y[2], &wgt);
        if (np >= 4)
        {
            /* "вычисленные" z[] */
            tx = x[0] * x[0] - x[1] * x[1];
            ty = x[0] * x[1];
            z[0] = a[0][0] + a[1][0] * x[0] - a[1][1] * x[1] + a[2][0] * tx - 2 * a[2][1] * ty;
            z[1] = a[0][1] + a[1][1] * x[0] + a[1][0] * x[1] + a[2][1] * tx + 2 * a[2][0] * ty;
            z[2] = a[0][2] + a[1][2] * x[2] + a[2][2] * x[2] * x[2];
            if (np >= 8)
            {
                for (i = 0; i < 3; i++)
                {
                    dy[i] = z[i] - y[i];
                    dzs[i] += (dy[i] * dy[i]) * wgt;
                }
                fprintf(fp1, format11, name, x[0], x[1], x[2], y[0], y[1], y[2], wgt, dy[0], dy[1], dy[2]);
            }
            else
            {
                for (i = 0; i < 3; i++)
                {
                    y[i] = z[i];
                }
                fprintf(fp1, format7, name, x[0], x[1], x[2], y[0], y[1], y[2]);
            }
        }
        else
        {
            if (np > 0)         /* no error for empty lines */
            {
                fprintf(stderr, "Error in input, lines kipped: \n%s\n", buf);
            }
        }
    }
    if (n > 0.0)
    {
        for (i = 0; i < 3; i++)
        {
            dzs[i] /= n;
        }
    }
    for (i = 0; i < 3; i++)
    {
        dzs[i] *= 2.0;
        dzs[i] = sqrt(dzs[i]);
    }
    fprintf(fp1, "\n");
    fprintf(fp1, "diff:\n");
    fprintf(fp1, format3, dzs[0], dzs[1], dzs[2]);
    fclose(fp1);
    fclose(fp0);

    return 0;
}
