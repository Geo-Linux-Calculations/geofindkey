/*
Name: geofindkey.c
OldName: findkey.c
Version: 2.8
Date: 2021-12-15
Author: Игорь Белов (https://gis-lab.info/forum/memberlist.php?mode=viewprofile&u=10457)
Author: zvezdochiot (https://github.com/zvezdochiot)
Author: Zoltan Siki (https://github.com/zsiki)
*
build:
$ gcc -o geofindkey geofindkey.c -lm
sample:
$ ./geofindkey doc/data.dat report.dat
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
(NORM)
--0-----
82135.4073
47128.1437
149.9631
--1-----
0.999787994227
-0.027289778074
1.000606333521
========
1.000160369835
-1.5635324426

var:
1 1334.7100 285.9400 66.2900 83477.6400 47377.6000 216.2800 1 -0.0024 -0.0008 +0.0133 -0.0002735462 -0.0000
2 563.6700 -5197.3400 60.2100 82557.1400 41916.5100 210.2100 1 -0.0165 +0.0132 -0.0004 0.0002137624 +0.0093
3 4444.2700 1153.7900 67.7600 86610.1900 48160.3900 217.7700 1 +0.0318 +0.0160 -0.0058 -0.0000341993 -0.0355
4 -252.0700 2881.9000 65.4100 81962.0500 50016.3400 215.4200 1 -0.0129 -0.0283 -0.0072 -0.0003963128 +0.0189
5 1334.7100 285.9400 66.2900 83477.6376 47377.5992 216.2933
6 563.6700 -5197.3400 60.2100 82557.1235 41916.5232 210.2096
7 4444.2700 1153.7900 67.7600 86610.2218 48160.4060 217.7642
8 -252.0700 2881.9000 65.4100 81962.0371 50016.3117 215.4128

diff:
0.0269 0.0248 0.0115 0.0003672639 0.0292
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define PNAME "GeoFindKey"
#define PVERSION "2.8"

#define defMScale "NORM"
#define defREarth 6370009.0

void geofindkeytitle()
{
    fprintf(stderr, "%s %s\n", PNAME, PVERSION);
}

void geofindkeyusage()
{
    fprintf(stderr, "usage: geofindkey [option] input-file report-file\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "          -d N    decimal after comma, default=4\n");
    fprintf(stderr, "          -m str  rescale mode {NORM,EQUAL,EARCH}, default=NORM\n");
    fprintf(stderr, "          -r N.N  radius Earth, default=6370009.0\n");
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
    fprintf(stderr, " (NORM)\n");
    fprintf(stderr, " --0-----\n");
    fprintf(stderr, " 82135.4073\n");
    fprintf(stderr, " 47128.1437\n");
    fprintf(stderr, " 149.9631\n");
    fprintf(stderr, " --1-----\n");
    fprintf(stderr, " 0.999787994227\n");
    fprintf(stderr, " -0.027289778074\n");
    fprintf(stderr, " 1.000606333521\n");
    fprintf(stderr, " ========\n");
    fprintf(stderr, " 1.000160369835\n");
    fprintf(stderr, " -1.5635324426\n");
    fprintf(stderr, " \n");
    fprintf(stderr, " var:\n");
    fprintf(stderr, " 1 1334.7100 285.9400 66.2900 83477.6400 47377.6000 216.2800 1 -0.0024 -0.0008 +0.0133 -0.0002735462 -0.0000\n");
    fprintf(stderr, " 2 563.6700 -5197.3400 60.2100 82557.1400 41916.5100 210.2100 1 -0.0165 +0.0132 -0.0004 0.0002137624 +0.0093\n");
    fprintf(stderr, " 3 4444.2700 1153.7900 67.7600 86610.1900 48160.3900 217.7700 1 +0.0318 +0.0160 -0.0058 -0.0000341993 -0.0355\n");
    fprintf(stderr, " 4 -252.0700 2881.9000 65.4100 81962.0500 50016.3400 215.4200 1 -0.0129 -0.0283 -0.0072 -0.0003963128 +0.0189\n");
    fprintf(stderr, " 5 1334.7100 285.9400 66.2900 83477.6376 47377.5992 216.2933\n");
    fprintf(stderr, " 6 563.6700 -5197.3400 60.2100 82557.1235 41916.5232 210.2096\n");
    fprintf(stderr, " 7 4444.2700 1153.7900 67.7600 86610.2218 48160.4060 217.7642\n");
    fprintf(stderr, " 8 -252.0700 2881.9000 65.4100 81962.0371 50016.3117 215.4128\n");
    fprintf(stderr, " \n");
    fprintf(stderr, " diff:\n");
    fprintf(stderr, " 0.0269 0.0248 0.0115 0.0003672639 0.0292\n");
}

int IndexMScale(char* mscale)
{
    if (!strcmp(mscale,"NORM"))
        return 0;
    if (!strcmp(mscale,"EQUAL"))
        return 1;
    if (!strcmp(mscale,"EARTH"))
        return 2;
    return 0;
}

int main(int argc, char *argv[])
{
    char buf[1024], name[32], format5[128], format7[128], format13[128];
    double x[3], y[3], z[3], wgt, n;
    double xc[4], yc[4];
    double dx[3], dy[3], dz[3], vdz[3];
    double a[2][3], scale, rotation, ay, az, da, say, saz, ds;
    double s[8];
    int i, np;
    FILE *fp0, *fp1;

    int opt;
    char* mscale;
    int decimals = 4;   /* number of decimals in the calculated coordinates */
    double RE = defREarth;
    int frescale = 0;
    mscale = defMScale;
    int fhelp = 0;
    while ((opt = getopt(argc, argv, "d:m:r:h")) != -1)
    {
        switch(opt)
        {
        case 'd':
            decimals = atoi(optarg);
            break;
        case 'm':
            mscale = optarg;
            break;
        case 'r':
            RE = atof(optarg);
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

    sprintf(format5, "%%.%df %%.%df %%.%df %%.10f %%.%df\n",
            decimals, decimals, decimals, decimals);
    sprintf(format7, "%%s %%.%df %%.%df %%.%df %%.%df %%.%df %%.%df\n",
            decimals, decimals, decimals, decimals, decimals, decimals);
    sprintf(format13, "%%s %%.%df %%.%df %%.%df %%.%df %%.%df %%.%df %%g %%+.%df %%+.%df %%+.%df %%.10f %%+.%df\n",
            decimals, decimals, decimals, decimals, decimals, decimals, decimals, decimals, decimals, decimals);
    geofindkeytitle();

    if ((optind + 2 > argc) || (fhelp > 0))
    {
        geofindkeyusage();
        exit(0);
    }

    if ((fp0 = fopen(argv[optind], "r")) == NULL)
    {
        fprintf(stderr, "can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    frescale = IndexMScale(mscale);
    if (frescale == 0) mscale = defMScale;

    /* подсчитать сумму координат */
    n = 0;
    for (i = 0; i < 8; i++)
    {
        s[i] = 0.0;
    }
    xc[3] = 0.0;
    yc[3] = 0.0;
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
    for (i = 0; i < 8; i++)
    {
        s[i] = 0.;
    }
    while (fgets(buf, 1024, fp0) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf %lf", name, &x[0], &x[1], &x[2], &y[0], &y[1], &y[2], &wgt);
        if (np >= 8)
        {
            /* вычислить разности */

            for (i = 0; i < 3; i++)
            {
                dx[i] = x[i] - xc[i];
                dy[i] = y[i] - yc[i];
            }
            dx[0] *= xc[3];
            dx[1] *= xc[3];
            dx[2] *= yc[3];
            /* суммировать */
            s[0] += dx[0] * dy[0] * wgt;
            s[1] += dx[1] * dy[1] * wgt;
            s[2] += dx[2] * dx[2] * wgt;
            s[3] += dx[0] * dy[1] * wgt;
            s[4] += dx[1] * dy[0] * wgt;
            s[5] += dy[2] * dx[2] * wgt;
            s[6] += (dx[0] * dx[0] + dx[1] * dx[1]) * wgt;
        }
    }
    rewind(fp0);

    /* найти первичные параметры */
    a[1][0] = (s[0] + s[1]) * xc[3];
    a[1][1] = (s[3] - s[4]) * xc[3];
    if (s[6] > 0.0)
    {
        a[1][0] /= s[6];
        a[1][1] /= s[6];
    }
    else
    {
        a[1][0] = 1.0;
        a[1][1] = 0.0;
    }
    if (s[2] > 0.0)
    {
        a[1][2] = s[5] / s[2] * yc[3];
    }
    else
    {
        a[1][2] = 1.0;
    }

    /* найти вторичные параметры */
    scale = hypot(a[1][0], a[1][1]);
    rotation = atan2(a[1][1], a[1][0]);

    if(frescale > 0)
    {
        if (scale > 0.0)
        {
            a[1][0] /= scale;
            a[1][1] /= scale;
        }
        a[1][2] = 1.0;
        if(frescale > 1)
        {
            if (RE > 0.0)
            {
                a[1][0] *= (1.0 - yc[2] / RE);
                a[1][1] *= (1.0 - yc[2] / RE);
            }
        }
    }

    a[0][0] = yc[0] - a[1][0] * xc[0] + a[1][1] * xc[1];
    a[0][1] = yc[1] - a[1][1] * xc[0] - a[1][0] * xc[1];
    a[0][2] = yc[2] - a[1][2] * xc[2];

    /* вывести параметры в файл ключа */
    if ((fp1 = fopen(argv[optind + 1], "w")) == NULL)
    {
        fprintf(stderr, "can't create %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    fprintf(fp1, "key:\n");
    fprintf(fp1, "(%s)\n", mscale);
    fprintf(fp1, "--0-----\n");
    fprintf(fp1, "%.4f\n", a[0][0]);
    fprintf(fp1, "%.4f\n", a[0][1]);
    fprintf(fp1, "%.4f\n", a[0][2]);
    fprintf(fp1, "--1-----\n");
    fprintf(fp1, "%.12f\n", a[1][0]);
    fprintf(fp1, "%.12f\n", a[1][1]);
    fprintf(fp1, "%.12f\n", a[1][2]);
    fprintf(fp1, "========\n");
    fprintf(fp1, "%.12f\n", scale);
    fprintf(fp1, "%+.10f\n", rotation * 180.0 / M_PI);
    fprintf(fp1, "\n");

    /* вывести данные вместе с невязками */
    fprintf(fp1, "var:\n");
    for (i = 0; i < 8; i++)
    {
        s[i] = 0.0;
    }
    while (fgets(buf, 1024, fp0) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf %lf", name, &x[0], &x[1], &x[2], &y[0], &y[1], &y[2], &wgt);
        if (np >= 4)
        {
            /* "наблюдённые" dx[], dy[] */
            for (i = 0; i < 3; i++)
            {
                dx[i] = x[i] - xc[i];
                dy[i] = y[i] - yc[i];
            }
            /* "вычисленные" dy[] */
            z[0] = a[0][0] + a[1][0] * x[0] - a[1][1] * x[1];
            z[1] = a[0][1] + a[1][1] * x[0] + a[1][0] * x[1];
            z[2] = a[0][2] + a[1][2] * x[2];
            if (np >= 8)
            {
                for (i = 0; i < 3; i++)
                {
                    dy[i] = y[i] - yc[i];
                    dz[i] = z[i] - yc[i];
                    vdz[i] = z[i] - y[i];
                    s[i] += (vdz[i] * vdz[i]) * wgt;
                }
                az = atan2(dz[1], dz[0]);
                saz = hypot(dz[0], dz[1]);
                ay = atan2(dy[1], dy[0]);
                say = hypot(dy[0], dy[1]);
                ds = say - saz;
                s[3] += ds * ds * wgt;
                da = ay - az;
                da *= 180. / M_PI;
                if (da > 180)
                {
                    da -= 360;
                }
                if (da < -180)
                {
                    da += 360;
                }
                s[4] += da * da * say * wgt;
                s[6] += say * wgt;
                fprintf(fp1, format13, name, x[0], x[1], x[2], y[0], y[1], y[2], wgt, vdz[0], vdz[1], vdz[2], da, ds);
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
        for (i = 0; i < 4; i++)
        {
            s[i] /= n;
        }
    }
    if (s[6] > 0.0)
    {
        s[4] /= s[6];
    }
    for (i = 0; i < 5; i++)
    {
        s[i] *= 2.0;
        s[i] = sqrt(s[i]);
    }
    fprintf(fp1, "\n");
    fprintf(fp1, "diff:\n");
    fprintf(fp1, format5, s[0], s[1], s[2], s[4], s[3]);
    fclose(fp1);
    fclose(fp0);

    return 0;
}
