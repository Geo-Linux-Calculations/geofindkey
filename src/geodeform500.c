/*
Name: geodeform500.c
Version: 3.1
Date: 2021-12-30
Author: zvezdochiot (https://github.com/zvezdochiot)
*
build:
$ gcc -o geodeform500 geodeform500.c -lm
sample:
$ ./geositer500 doc/gps.dat gpsout.dat
*
file:
input file doc/gps.dat:
*
A             2303.443 5622.903 149.307 2302.854 5623.223 148.856 1.0
B             2474.753 5830.133 114.434 2474.540 5829.768 114.844 1.0
C             2748.516 5313.559 109.125 2748.808 5314.058 109.855 1.0
(2a+3b+5c)/10 2577.372 5530.400 118.754
(a+8b+c)/10   2484.998 5757.752 117.390
(6a+2b+2c)/10 2426.719 5602.480 134.296
a             2303.443 5622.903 149.307
b             2474.753 5830.133 114.434
c             2748.516 5313.559 109.125
(a+b)/2       2389.098 5726.518 131.870
(a+c)/2       2525.980 5468.231 129.216
(b+c)/2       2611.635 5571.846 111.779
A*            2302.854 5623.223 148.856
B*            2474.540 5829.768 114.844
C*            2748.808 5314.058 109.855
*
output file gpsout.dat:
*
Mean: 3
M 2508.9040 5588.8650 124.2887 2508.7340 5589.0163 124.5183
Deformation coordinate base: 3
(CONST)
A 2303.4430 5622.9030 149.3070 2302.8540 5623.2230 148.8560
B 2474.7530 5830.1330 114.4340 2474.5400 5829.7680 114.8440
C 2748.5160 5313.5590 109.1250 2748.8080 5314.0580 109.8550
(2a+3b+5c)/10 2577.3720 5530.4000 118.7540 2577.2210 5530.5915 118.9920
(a+8b+c)/10 2484.9980 5757.7520 117.3900 2484.7597 5757.4651 117.7270
(6a+2b+2c)/10 2426.7190 5602.4800 134.2960 2426.2635 5602.6663 134.0994
a 2303.4430 5622.9030 149.3070 2302.8540 5623.2230 148.8560
b 2474.7530 5830.1330 114.4340 2474.5400 5829.7680 114.8440
c 2748.5160 5313.5590 109.1250 2748.8080 5314.0580 109.8550
(a+b)/2 2389.0980 5726.5180 131.8700 2388.7176 5726.5110 131.8718
(a+c)/2 2525.9800 5468.2310 129.2160 2525.8176 5468.4730 129.4140
(b+c)/2 2611.6350 5571.8460 111.7790 2611.4850 5571.9893 112.0412
A* 2302.8540 5623.2230 148.8560 2302.2650 5623.5430 148.4050
B* 2474.5400 5829.7680 114.8440 2474.3270 5829.4030 115.2540
C* 2748.8080 5314.0580 109.8550 2749.1000 5314.5570 110.5850
*
*/

#include "geofindkey.h"

#define PNAME "GeoDeform500"

void geodeform500title()
{
    fprintf(stderr, "%s %s\n", PNAME, PVERSION);
}

void geodeform500usage()
{
    fprintf(stderr, "usage: geodeform500 [option] input-file report-file\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "          -d N    decimal after comma, default=%d\n", defDecimals);
    fprintf(stderr, "          -e N.N  eps, default=%g\n", defEps);
    fprintf(stderr, "          -m str  base mode {CONST,VAR}, default=%s\n", defMode);
    fprintf(stderr, "          -h      this help\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "input-file(sample):\n");
    fprintf(stderr, " A             2303.443 5622.903 149.307 2302.854 5623.223 148.856 1.0\n");
    fprintf(stderr, " B             2474.753 5830.133 114.434 2474.540 5829.768 114.844 1.0\n");
    fprintf(stderr, " C             2748.516 5313.559 109.125 2748.808 5314.058 109.855 1.0\n");
    fprintf(stderr, " (2a+3b+5c)/10 2577.372 5530.400 118.754\n");
    fprintf(stderr, " (a+8b+c)/10   2484.998 5757.752 117.390\n");
    fprintf(stderr, " (6a+2b+2c)/10 2426.719 5602.480 134.296\n");
    fprintf(stderr, " a             2303.443 5622.903 149.307\n");
    fprintf(stderr, " b             2474.753 5830.133 114.434\n");
    fprintf(stderr, " c             2748.516 5313.559 109.125\n");
    fprintf(stderr, " (a+b)/2       2389.098 5726.518 131.870\n");
    fprintf(stderr, " (a+c)/2       2525.980 5468.231 129.216\n");
    fprintf(stderr, " (b+c)/2       2611.635 5571.846 111.779\n");
    fprintf(stderr, " A*            2302.854 5623.223 148.856\n");
    fprintf(stderr, " B*            2474.540 5829.768 114.844\n");
    fprintf(stderr, " C*            2748.808 5314.058 109.855\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "report-file(sample):\n");
    fprintf(stderr, " Mean: 3\n");
    fprintf(stderr, " M 2508.9040 5588.8650 124.2887 2508.7340 5589.0163 124.5183\n");
    fprintf(stderr, " Deformation coordinate base: 3\n");
    fprintf(stderr, " (CONST)\n");
    fprintf(stderr, " A 2303.4430 5622.9030 149.3070 2302.8540 5623.2230 148.8560\n");
    fprintf(stderr, " B 2474.7530 5830.1330 114.4340 2474.5400 5829.7680 114.8440\n");
    fprintf(stderr, " C 2748.5160 5313.5590 109.1250 2748.8080 5314.0580 109.8550\n");
    fprintf(stderr, " (2a+3b+5c)/10 2577.3720 5530.4000 118.7540 2577.2210 5530.5915 118.9920\n");
    fprintf(stderr, " (a+8b+c)/10 2484.9980 5757.7520 117.3900 2484.7597 5757.4651 117.7270\n");
    fprintf(stderr, " (6a+2b+2c)/10 2426.7190 5602.4800 134.2960 2426.2635 5602.6663 134.0994\n");
    fprintf(stderr, " a 2303.4430 5622.9030 149.3070 2302.8540 5623.2230 148.8560\n");
    fprintf(stderr, " b 2474.7530 5830.1330 114.4340 2474.5400 5829.7680 114.8440\n");
    fprintf(stderr, " c 2748.5160 5313.5590 109.1250 2748.8080 5314.0580 109.8550\n");
    fprintf(stderr, " (a+b)/2 2389.0980 5726.5180 131.8700 2388.7176 5726.5110 131.8718\n");
    fprintf(stderr, " (a+c)/2 2525.9800 5468.2310 129.2160 2525.8176 5468.4730 129.4140\n");
    fprintf(stderr, " (b+c)/2 2611.6350 5571.8460 111.7790 2611.4850 5571.9893 112.0412\n");
    fprintf(stderr, " A* 2302.8540 5623.2230 148.8560 2302.2650 5623.5430 148.4050\n");
    fprintf(stderr, " B* 2474.5400 5829.7680 114.8440 2474.3270 5829.4030 115.2540\n");
    fprintf(stderr, " C* 2748.8080 5314.0580 109.8550 2749.1000 5314.5570 110.5850\n");
}

int main(int argc, char *argv[])
{
    char buf[1024], name[32], format4[128], format7[128];
    double x[3], y[3], xcp[3], ycp[3], wgt, dy[3];
    double xd[1500], dxd[1500], r2, r2d[500], w[500], wgts, s;
    unsigned n, i, j, k;
    int np;
    FILE *fpin, *fpout;

    int opt;
    double eps = defEps;
    char* mbase = defMode;
    int decimals = defDecimals;   /* number of decimals in the calculated coordinates */
    int fhelp = 0;
    while ((opt = getopt(argc, argv, "d:e:m:h")) != -1)
    {
        switch(opt)
        {
        case 'h':
            fhelp = 1;
            break;
        case 'd':
            decimals = atoi(optarg);
            break;
        case 'e':
            eps = atof(optarg);
            break;
        case 'm':
            mbase = optarg;
            break;
        case ':':
            fprintf(stderr, "option needs a value\n");
            break;
        case '?':
            fprintf(stderr, "unknown option: %c\n", optopt);
            break;
        }
    }

    sprintf(format4, "%%s %%.%df %%.8f %%.8f\n",
            decimals);
    sprintf(format7, "%%s %%.%df %%.%df %%.%df %%.%df %%.%df %%.%df\n",
            decimals, decimals, decimals, decimals, decimals, decimals);
    geodeform500title();

    if ((optind + 2 > argc) || (fhelp > 0))
    {
        geodeform500usage();
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

    for (j = 0; j < 3; j++)
    {
        xcp[j] = 0.0;
        ycp[j] = 0.0;
    }
    n = 0;
    wgts = 0;
    while (fgets(buf, 1024, fpin) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf %lf", name, &x[0], &x[1], &x[2], &y[0], &y[1], &y[2], &wgt);
        if (np >= 8)
        {
            for (i = 0; i < 3; i++)
            {
                xcp[i] += (x[i] * wgt);
                ycp[i] += (y[i] * wgt);
            }
            wgts += wgt;
            n++;
        }
    }
    if (wgts > 0.0)
    {
        for (j = 0; j < 3; j++)
        {
            xcp[j] /= wgts;
            ycp[j] /= wgts;
        }
        fprintf(fpout, "Mean: %d\n", n);
        fprintf(fpout, format7, "M", xcp[0], xcp[1], xcp[2], ycp[0], ycp[1], ycp[2]);
        rewind(fpin);

        for (j = 0; j < 1500; j++)
        {
            xd[j] = 0.0;
        }
        n = 0;
        while (fgets(buf, 1024, fpin) != NULL)
        {
            np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf %lf", name, &x[0], &x[1], &x[2], &y[0], &y[1], &y[2], &wgt);
            if (np >= 8)
            {
                if ((n < 499) && (wgt > 0.0))
                {
                    j = 3 * n;
                    r2 = eps * eps;
                    for (i = 0; i < 3; i++)
                    {
                        xd[j + i] = x[i];
                        dxd[j + i] = (y[i] - ycp[i]) - (x[i] - xcp[i]);
                        r2 += (dxd[i + j] * dxd[i + j]);
                    }
                    r2d[n] = r2 * wgt;
                    n++;
                }
            }
        }
        fprintf(fpout, "Deformation coordinate base: %d\n", n);
        fprintf(fpout, "(%s)\n", mbase);
        rewind(fpin);

        j = 0;
        while (fgets(buf, 1024, fpin) != NULL)
        {
            np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf %lf", name, &x[0], &x[1], &x[2], &y[0], &y[1], &y[2], &wgt);
            if (np >= 4)
            {
                s = 0.0;
                for (i = 0; i < n; i++)
                {
                    if (r2d[i] >= 0.0)
                    {
                        j = 3 * i;
                        r2 = r2d[i];
                        for (k = 0; k < 3; k++)
                        {
                            dy[k] = xd[j + k] - x[k];
                            r2 += (dy[k] * dy[k]);
                        }
                        if (!strcmp(mbase,"VAR"))
                            w[i] = r2d[i] / r2;
                        else
                            w[i] = 1.0 / r2;
                        w[i] *= wgt;
                        s += w[i];
                    }
                    else
                    {
                        w[i] = 0.0;
                    }
                }
                if (s > 0.0)
                {
                    s = 1.0 / s;
                    for (i = 0; i < n; i++)
                    {
                        w[i] *= s;
                    }
                    for (i = 0; i < 3; i++)
                    {
                        k = i;
                        dy[i] = 0;
                        for (j = 0; j < n; j++)
                        {
                            dy[i] += dxd[k] * w[j];
                            k += 3;
                        }
                        y[i] = x[i] + dy[i] + (ycp[i] - xcp[i]);
                    }
                }
                else
                {
                    for (i = 0; i < 3; i++)
                    {
                        y[i] = x[i];
                    }
                }
                fprintf(fpout, format7, name, x[0], x[1], x[2], y[0], y[1], y[2]);
            }
            else
            {
                if (np > 0)         /* no error for empty lines */
                {
                    fprintf(stderr, "Error in input, lines kipped: \n%s\n", buf);
                }
            }
        }
    }
    else
    {
        fprintf(fpout, "No mating points found! Calculation is not possible!\n");
    }
    fclose(fpout);
    fclose(fpin);

    return 0;
}
