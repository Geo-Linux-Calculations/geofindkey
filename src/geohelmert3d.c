/*
Name: geohelmert3d.c
(use Gauss normalize @zvezdochiot[https://geodesist.ru/members/zvezdochiot.47244/])
(use Last published version of CCMATH by Daniel Atkinson in 2001 (version 2.2.1)[https://github.com/mnhrdt/ccmath].)
Version: 3.1
Date: 2021-12-30
Author: Игорь Белов (https://gis-lab.info/forum/memberlist.php?mode=viewprofile&u=10457)
Author: zvezdochiot (https://github.com/zvezdochiot)
Author: Zoltan Siki (https://github.com/zsiki)
*
build:
$ gcc -o geohelmert3d geohelmert3d.c -lm
sample:
$ ./geohelmert3d doc/data.dat report.dat
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
Mean: 4
M 1522.6450 -218.9275 64.9175 83651.7550 46867.7100 214.9200
NORM = 0.000285193
cond(G) = 7.24047
Units: DEG
key:
 82135.4074
 47128.1438
 150.0150
 -212.0052
 6.71662e-05
 -5.55191e-05
 -1.56359

var:
1 1334.7100 285.9400 66.2900 83477.6400 47377.6000 216.2800 1 -0.0024 -0.0008 +0.0126
2 563.6700 -5197.3400 60.2100 82557.1400 41916.5100 210.2100 1 -0.0165 +0.0132 -0.0033
3 4444.2700 1153.7900 67.7600 86610.1900 48160.3900 217.7700 1 +0.0318 +0.0160 -0.0037
4 -252.0700 2881.9000 65.4100 81962.0500 50016.3400 215.4200 1 -0.0129 -0.0283 -0.0057
5 1334.7100 285.9400 66.2900 83477.6376 47377.5992 216.2926
6 563.6700 -5197.3400 60.2100 82557.1235 41916.5232 210.2067
7 4444.2700 1153.7900 67.7600 86610.2218 48160.4060 217.7663
8 -252.0700 2881.9000 65.4100 81962.0371 50016.3117 215.4143

diff:
0.0269 0.0248 0.0104
*
*/

#include "geofindkey.h"

#define PNAME "GeoHelmert3D"

void geohelmert3dtitle()
{
    fprintf(stderr, "%s %s\n", PNAME, PVERSION);
}

void geohelmert3dusage()
{
    fprintf(stderr, "usage: geohelmert3d [option] input-file report-file\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "          -d N    decimal after comma, default=%d\n", defDecimals);
    fprintf(stderr, "          -u str  units angles {RAD,DEG,GON,DMS}, default=%s\n", defUnits);
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
    fprintf(stderr, " Mean: 4\n");
    fprintf(stderr, " M 1522.6450 -218.9275 64.9175 83651.7550 46867.7100 214.9200\n");
    fprintf(stderr, " NORM = 0.000285193\n");
    fprintf(stderr, " cond(G) = 7.24047\n");
    fprintf(stderr, " Units: DEG\n");
    fprintf(stderr, " key:\n");
    fprintf(stderr, "  82135.4074\n");
    fprintf(stderr, "  47128.1438\n");
    fprintf(stderr, "  150.0150\n");
    fprintf(stderr, "  -212.0052\n");
    fprintf(stderr, "  6.71662e-05\n");
    fprintf(stderr, "  -5.55191e-05\n");
    fprintf(stderr, "  -1.56359\n");
    fprintf(stderr, " \n");
    fprintf(stderr, " var:\n");
    fprintf(stderr, " 1 1334.7100 285.9400 66.2900 83477.6400 47377.6000 216.2800 1 -0.0024 -0.0008 +0.0126\n");
    fprintf(stderr, " 2 563.6700 -5197.3400 60.2100 82557.1400 41916.5100 210.2100 1 -0.0165 +0.0132 -0.0033\n");
    fprintf(stderr, " 3 4444.2700 1153.7900 67.7600 86610.1900 48160.3900 217.7700 1 +0.0318 +0.0160 -0.0037\n");
    fprintf(stderr, " 4 -252.0700 2881.9000 65.4100 81962.0500 50016.3400 215.4200 1 -0.0129 -0.0283 -0.0057\n");
    fprintf(stderr, " 5 1334.7100 285.9400 66.2900 83477.6376 47377.5992 216.2926\n");
    fprintf(stderr, " 6 563.6700 -5197.3400 60.2100 82557.1235 41916.5232 210.2067\n");
    fprintf(stderr, " 7 4444.2700 1153.7900 67.7600 86610.2218 48160.4060 217.7663\n");
    fprintf(stderr, " 8 -252.0700 2881.9000 65.4100 81962.0371 50016.3117 215.4143\n");
    fprintf(stderr, " \n");
    fprintf(stderr, " diff:\n");
    fprintf(stderr, " 0.0269 0.0248 0.0104\n");
}

int ANGLEID(char* units)
{
    if (!strcmp(units,"RAD"))
        return 0;
    if (!strcmp(units,"DEG"))
        return 1;
    if (!strcmp(units,"DMS"))
        return 2;
    if (!strcmp(units,"GON"))
        return 3;
    return 0;
}

int main(int argc, char *argv[])
{
    char buf[1024], name[128], format1[128], format3[128], format7[128], format11[128];
    double x[3], y[3], z[3], xcp[3], ycp[3], xs[3], dz[3], wgt, wgts, n, gnorm, ku;
    double *gmat, gvec[4], hparam[7], condg;

    unsigned i, j, t;
    int np;
    FILE *fpin, *fpout;

    int opt;
    int decimals = defDecimals;   /* number of decimals in the calculated coordinates */
    char* units = defUnits;
    int fhelp = 0;

    gmat = (double *)malloc(16 * sizeof(double));

    while ((opt = getopt(argc, argv, "d:u:h")) != -1)
    {
        switch(opt)
        {
        case 'd':
            decimals = atoi(optarg);
            break;
        case 'h':
            fhelp = 1;
            break;
        case 'u':
            units = optarg;
            break;
        case ':':
            fprintf(stderr, "option needs a value\n");
            break;
        case '?':
            fprintf(stderr, "unknown option: %c\n", optopt);
            break;
        }
    }

    sprintf(format1, " %%.%df\n", decimals);
    sprintf(format3, "%%.%df %%.%df %%.%df\n",
            decimals, decimals, decimals);
    sprintf(format7, "%%s %%.%df %%.%df %%.%df %%.%df %%.%df %%.%df\n",
            decimals, decimals, decimals, decimals, decimals, decimals);
    sprintf(format11, "%%s %%.%df %%.%df %%.%df %%.%df %%.%df %%.%df %%g %%+.%df %%+.%df %%+.%df\n",
            decimals, decimals, decimals, decimals, decimals, decimals, decimals, decimals, decimals);
    geohelmert3dtitle();

    if ((optind + 2 > argc) || (fhelp > 0))
    {
        geohelmert3dusage();
        exit(0);
    }

    if ((fpin = fopen(argv[optind], "r")) == NULL)
    {
        fprintf(stderr, "can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ((fpout = fopen(argv[optind + 1], "w")) == NULL)
    {
        fprintf(stderr, "can't create %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    t = ANGLEID(units);
    for (j = 0; j < 3; j++)
    {
        xcp[j] = 0.0;
        ycp[j] = 0.0;
        xs[j] = 0.0;
    }
    n = 0.0;
    wgts = 0.0;
    while (fgets(buf, 1024, fpin) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf %lf", name, &x[0], &x[1], &x[2], &y[0], &y[1], &y[2], &wgt);
        if (np >= 8)
        {
            for (i = 0; i < 3; i++)
            {
                xcp[i] += (x[i] * wgt);
                ycp[i] += (y[i] * wgt);
                xs[i] += (x[i] * x[i] * wgt);
            }
            wgts += wgt;
            n++;
        }
    }
    if (n > 0.0)
    {
        n = (wgts > 0.0) ? wgts : n;
        gnorm = 0.0;
        for (j = 0; j < 3; j++)
        {
            xcp[j] /= n;
            ycp[j] /= n;
            xs[j] /= n;
            xs[j] -= (xcp[j] * xcp[j]);
            gnorm += xs[j];
        }
        gnorm = (gnorm > 0) ? (1.0 / sqrt(gnorm)) : 1.0;
        fprintf(fpout, "Mean: %g\n", n);
        fprintf(fpout, format7, "M", xcp[0], xcp[1], xcp[2], ycp[0], ycp[1], ycp[2]);
        fprintf(fpout, "NORM = %g\n", gnorm);
        rewind(fpin);

        for (j = 0; j < 16; j++)
        {
            gmat[j] = 0.0;
        }
        for (j = 0; j < 4; j++)
        {
            gvec[j] = 0.0;
        }
        for (j = 0; j < 3; j++)
        {
            xs[j] = 0.0;
        }
        while (fgets(buf, 1024, fpin) != NULL)
        {
            np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf %lf", name, &x[0], &x[1], &x[2], &y[0], &y[1], &y[2], &wgt);
            if (np >= 8)
            {
                for (i = 0; i < 3; i++)
                {
                    x[i] = gaussnorm(x[i], xcp[i], gnorm);
                    xs[i] = (x[i] * x[i] * wgt);
                    y[i] = gaussnorm(y[i], ycp[i], gnorm);
                }
                gmat[0] += (xs[0] + xs[1] + xs[2]);
                gmat[5] += (xs[1] + xs[2]);
                gmat[6] -= (x[0] * x[1] * wgt);
                gmat[7] -= (x[0] * x[2] * wgt);
                gmat[10] += xs[0] + xs[2];
                gmat[11] -= (x[1] * x[2] * wgt);
                gmat[15] += xs[0] + xs[1];
                gvec[0] += ((x[0] * y[0] + x[1] * y[1] + x[2] * y[2]) * wgt);
                gvec[1] += ((x[1] * y[2] - x[2] * y[1]) * wgt);
                gvec[2] += ((x[2] * y[0] - x[0] * y[2]) * wgt);
                gvec[3] += ((x[0] * y[1] - x[1] * y[0]) * wgt);
            }
        }
        gmat[9] = gmat[6];
        gmat[13] = gmat[7];
        gmat[14] = gmat[11];
        condg = minv(gmat, 4);
        fprintf(fpout, "cond(G) = %g\n", condg);
        rewind(fpin);

        if (condg > 0.0)
        {
            fprintf(fpout, "Units: %s\n", units);
            for (i = 0; i < 4; i++)
            {
                hparam[i + 3] = 0.0;
                for (j = 0; j < 4; j++)
                {
                    hparam[i + 3] += gmat[i * 4 + j] * gvec[j];
                }
            }
            hparam[0] = ycp[0] - hparam[3] * xcp[0] + hparam[6] * xcp[1] - hparam[5] * xcp[2];
            hparam[1] = ycp[1] - hparam[3] * xcp[1] + hparam[4] * xcp[2] - hparam[6] * xcp[0];
            hparam[2] = ycp[2] - hparam[3] * xcp[2] + hparam[5] * xcp[0] - hparam[4] * xcp[1];
            fprintf(fpout, "key:\n");
            for (j = 0; j < 3; j++)
            {
                fprintf(fpout, format1, hparam[j]);
            }
            switch(t)
            {
            case 1:
                ku = 180.0 / M_PI;
                fprintf(fpout, format1, ((hparam[3] - 1.0) * 1e6));
                for (j = 4; j < 7; j++)
                {
                    fprintf(fpout, " %g\n", (hparam[j] * ku));
                }
                break;
            case 2:
                ku = 180.0 * 60.0 * 60.0 / M_PI;
                fprintf(fpout, format1, ((hparam[3] - 1.0) * 1e6));
                for (j = 4; j < 7; j++)
                {
                    fprintf(fpout, format1, (hparam[j] * ku));
                }
                break;
            case 3:
                ku = 200.0 / M_PI;
                fprintf(fpout, format1, ((hparam[3] - 1.0) * 1e6));
                for (j = 4; j < 7; j++)
                {
                    fprintf(fpout, " %g\n", (hparam[j] * ku));
                }
                break;
            case 0:
            default:
                fprintf(fpout, " %.12f\n", hparam[3]);
                for (j = 4; j < 7; j++)
                {
                    fprintf(fpout, " %g\n", hparam[j]);
                }
                break;
            }
            fprintf(fpout, "\n");

            for (j = 0; j < 3; j++)
            {
                xs[j] = 0.0;
            }
            fprintf(fpout, "var:\n");
            while (fgets(buf, 1024, fpin) != NULL)
            {
                np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf %lf", name, &x[0], &x[1], &x[2], &y[0], &y[1], &y[2], &wgt);
                if (np >= 4)
                {
                    z[0] = hparam[0] + hparam[3] * x[0] - hparam[6] * x[1] + hparam[5] * x[2];
                    z[1] = hparam[1] + hparam[3] * x[1] + hparam[6] * x[0] - hparam[4] * x[2];
                    z[2] = hparam[2] + hparam[3] * x[2] - hparam[5] * x[0] + hparam[4] * x[1];
                    if (np >= 8)
                    {
                        for (i = 0; i < 3; i++)
                        {
                            dz[i] = z[i] - y[i];
                            xs[i] += (dz[i] * dz[i]) * wgt;
                        }
                        fprintf(fpout, format11, name, x[0], x[1], x[2], y[0], y[1], y[2], wgt, dz[0], dz[1], dz[2]);
                    }
                    else
                    {
                        fprintf(fpout, format7, name, x[0], x[1], x[2], z[0], z[1], z[2]);
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
                    xs[i] /= n;
                }
            }
            for (i = 0; i < 3; i++)
            {
                xs[i] *= 2.0;
                xs[i] = sqrt(xs[i]);
            }
            fprintf(fpout, "\n");
            fprintf(fpout, "diff:\n");
            fprintf(fpout, format3, xs[0], xs[1], xs[2]);
        }
        else
        {
            fprintf(fpout, "The calculation is wrong!\n");
        }
    }
    else
    {
        fprintf(fpout, "No mating points found! Calculation is not possible!\n");
    }
    free(gmat);
    fclose(fpout);
    fclose(fpin);

    return 0;
}
