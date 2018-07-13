/*
Name: geositer500.c
Version: 1.7
Date: 2018-07-13
Author: zvezdochiot (https://github.com/zvezdochiot)
*
build:
$ gcc -o geositer500 geositer500.c -lm
sample:
$ ./geositer500 doc/szbunknow.dat szb.dat
*
file:
input file doc/szbunknow.dat:
*
OKD-4     -1     74.08666667   234.38916667  7471.2970  14588.7117  98.7445
OKD-5     -1     81.18888889   254.73888889  7474.2548  14589.4514  97.7433
OKD-K3-1  -1     82.43944444   339.05361111  7477.0949  14580.7517  96.8713
OKD-K3-4  -1     70.66833333   161.16        7469.9723  14580.8231  97.6075
OKD-K5P   -1     71.95527778   137.52222222  7469.9811  14579.3211  97.6057
OKD-K7L   -1     83.96444444   17.82444444   7477.1099  14577.8330  96.8789
OKD-K7L   -1     276.03361111  197.82722222  7477.1099  14577.8330  96.8789
OKD-K5P   -1     288.04361111  317.52472222  7469.9811  14579.3211  97.6057
OKD-K3-4  -1     289.32972222  341.16111111  7469.9723  14580.8231  97.6075
OKD-K3-1  -1     277.55583333  159.05805556  7477.0949  14580.7517  96.8713
OKD-5     -1     278.80944444  74.74055556   7474.2548  14589.4514  97.7433
OKD-4     -1     285.91444444  54.38972222   7471.2970  14588.7117  98.7445
OKD-11    3.889  71.6025       313.60777778
OKD-12    3.889  288.39138889  133.60805556
*
output file szb.dat:
*
OKD-4 8.6045 74.08666667 234.38916667 7471.2970 14588.7117 98.7445
OKD-5 8.8697 81.18888889 254.73888889 7474.2548 14589.4514 97.7433
OKD-K3-1 3.6731 82.43944444 339.05361111 7477.0949 14580.7517 96.8713
OKD-K3-4 3.6912 70.66833333 161.16000000 7469.9723 14580.8231 97.6075
OKD-K5P 3.9388 71.95527778 137.52222222 7469.9811 14579.3211 97.6057
OKD-K7L 4.6861 83.96444444 17.82444444 7477.1099 14577.8330 96.8789
OKD-K7L 4.6861 276.03361111 197.82722222 7477.1099 14577.8330 96.8789
OKD-K5P 3.9388 288.04361111 317.52472222 7469.9811 14579.3211 97.6057
OKD-K3-4 3.6912 289.32972222 341.16111111 7469.9723 14580.8231 97.6075
OKD-K3-1 3.6731 277.55583333 159.05805556 7477.0949 14580.7517 96.8713
OKD-5 8.8697 278.80944444 74.74055556 7474.2548 14589.4514 97.7433
OKD-4 8.6045 285.91444444 54.38972222 7471.2970 14588.7117 98.7445
OKD-11 3.8890 71.60250000 313.60777778
OKD-12 3.8890 288.39138889 133.60805556
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define PNAME "GeoSIter500"
#define PVERSION "1.7"

void geositer500title()
{
    fprintf(stderr, "%s %s\n", PNAME, PVERSION);
}

void geositer500usage()
{
    fprintf(stderr, "usage: geositer500 [option] input-file report-file\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "          -h      this help\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "input-file(sample):\n");
    fprintf(stderr, " OKD-4     -1     74.08666667   234.38916667  7471.2970  14588.7117  98.7445\n");
    fprintf(stderr, " OKD-5     -1     81.18888889   254.73888889  7474.2548  14589.4514  97.7433\n");
    fprintf(stderr, " OKD-K3-1  -1     82.43944444   339.05361111  7477.0949  14580.7517  96.8713\n");
    fprintf(stderr, " OKD-K3-4  -1     70.66833333   161.16        7469.9723  14580.8231  97.6075\n");
    fprintf(stderr, " OKD-K5P   -1     71.95527778   137.52222222  7469.9811  14579.3211  97.6057\n");
    fprintf(stderr, " OKD-K7L   -1     83.96444444   17.82444444   7477.1099  14577.8330  96.8789\n");
    fprintf(stderr, " OKD-K7L   -1     276.03361111  197.82722222  7477.1099  14577.8330  96.8789\n");
    fprintf(stderr, " OKD-K5P   -1     288.04361111  317.52472222  7469.9811  14579.3211  97.6057\n");
    fprintf(stderr, " OKD-K3-4  -1     289.32972222  341.16111111  7469.9723  14580.8231  97.6075\n");
    fprintf(stderr, " OKD-K3-1  -1     277.55583333  159.05805556  7477.0949  14580.7517  96.8713\n");
    fprintf(stderr, " OKD-5     -1     278.80944444  74.74055556   7474.2548  14589.4514  97.7433\n");
    fprintf(stderr, " OKD-4     -1     285.91444444  54.38972222   7471.2970  14588.7117  98.7445\n");
    fprintf(stderr, " OKD-11    3.889  71.6025       313.60777778\n");
    fprintf(stderr, " OKD-12    3.889  288.39138889  133.60805556\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "report-file(sample):\n");
    fprintf(stderr, " OKD-4 8.6045 74.08666667 234.38916667 7471.2970 14588.7117 98.7445\n");
    fprintf(stderr, " OKD-5 8.8697 81.18888889 254.73888889 7474.2548 14589.4514 97.7433\n");
    fprintf(stderr, " OKD-K3-1 3.6731 82.43944444 339.05361111 7477.0949 14580.7517 96.8713\n");
    fprintf(stderr, " OKD-K3-4 3.6912 70.66833333 161.16000000 7469.9723 14580.8231 97.6075\n");
    fprintf(stderr, " OKD-K5P 3.9388 71.95527778 137.52222222 7469.9811 14579.3211 97.6057\n");
    fprintf(stderr, " OKD-K7L 4.6861 83.96444444 17.82444444 7477.1099 14577.8330 96.8789\n");
    fprintf(stderr, " OKD-K7L 4.6861 276.03361111 197.82722222 7477.1099 14577.8330 96.8789\n");
    fprintf(stderr, " OKD-K5P 3.9388 288.04361111 317.52472222 7469.9811 14579.3211 97.6057\n");
    fprintf(stderr, " OKD-K3-4 3.6912 289.32972222 341.16111111 7469.9723 14580.8231 97.6075\n");
    fprintf(stderr, " OKD-K3-1 3.6731 277.55583333 159.05805556 7477.0949 14580.7517 96.8713\n");
    fprintf(stderr, " OKD-5 8.8697 278.80944444 74.74055556 7474.2548 14589.4514 97.7433\n");
    fprintf(stderr, " OKD-4 8.6045 285.91444444 54.38972222 7471.2970 14588.7117 98.7445\n");
    fprintf(stderr, " OKD-11 3.8890 71.60250000 313.60777778\n");
    fprintf(stderr, " OKD-12 3.8890 288.39138889 133.60805556\n");
}

int main(int argc, char *argv[])
{
    char buf[1024], name[32];
    double x[3], y[3], z[3], dy[3], dz[3], s[6], a[2];
    double yc[3], zc[3];
    double siter[500], st, ds, sds;
    unsigned n, i, j, k;
    int np;
    FILE *fp0, *fp1;

    int opt;
    int fhelp = 0;
    while ((opt = getopt(argc, argv, ":h")) != -1)
    {
        switch(opt)
        {
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

    geositer500title();

    if ((optind + 2 > argc) || (fhelp > 0))
    {
        geositer500usage();
        exit(0);
    }

    if ((fp0 = fopen(argv[optind], "r")) == NULL)
    {
        fprintf(stderr, "can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ((fp1 = fopen(argv[optind + 1], "w")) == NULL)
    {
        fprintf(stderr, "can't create %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    n = 0;
    for (j = 0; j < 500; j++)
    {
        siter[j] = 1.0;
    }
    while (fgets(buf, 1024, fp0) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf ", name, &x[0], &x[1], &x[2], &z[0], &z[1], &z[2]);
        if (np >= 7)
        {
            if (x[0] < 0)
            {
                n++;
            }
        }
    }
    printf("Unknow distance: %d\n", n);
    rewind(fp0);

    sds = 1.0;
    k = 0;
    while (sds > 0.00000000001)
    {
        for (i = 0; i < 3; i++)
        {
            yc[i] = 0;
            zc[i] = 0;
        }
        n = 0;
        j = 0;
        while (fgets(buf, 1024, fp0) != NULL)
        {
            np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf ", name, &x[0], &x[1], &x[2], &z[0], &z[1], &z[2]);
            if (np >= 7)
            {
                if (x[0] < 0 && j < 500)
                {
                    x[0] = siter[j];
                    j++;
                }
                x[1] = 90 - x[1];;
                x[1] *= M_PI;
                x[1] /= 180.0;
                x[2] *= M_PI;
                x[2] /= 180.0;
                y[2] = x[0] * sin(x[1]);
                x[0] *= cos(x[1]);
                y[0] = x[0] * sin(x[2]);
                y[1] = x[0] * cos(x[2]);
                for (i = 0; i < 3; i++)
                {
                    yc[i] += y[i];
                    zc[i] += z[i];
                }
                n++;
            }
        }
        if (n > 0)
        {
            for (i = 0; i < 3; i++)
            {
                yc[i] /= n;
                zc[i] /= n;
            }
       }
        rewind(fp0);

        for (i = 0; i < 6; i++) {s[i] = 0;}
        j = 0;
        while (fgets(buf, 1024, fp0) != NULL)
        {
            np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf ", name, &x[0], &x[1], &x[2], &z[0], &z[1], &z[2]);
            if (np >= 7)
            {
                if (x[0] < 0 && j < 500)
                {
                    x[0] = siter[j];
                    j++;
                }
                x[1] = 90 - x[1];;
                x[1] *= M_PI;
                x[1] /= 180.0;
                x[2] *= M_PI;
                x[2] /= 180.0;
                y[2] = x[0] * sin(x[1]);
                x[0] *= cos(x[1]);
                y[0] = x[0] * sin(x[2]);
                y[1] = x[0] * cos(x[2]);
                for (i = 0; i < 3; i++)
                {
                    dy[i] = y[i] - yc[i];
                    dz[i] = z[i] - zc[i];
                }
                s[0] += dy[0] * dz[0];
                s[1] += dy[1] * dz[1];
                s[2] += dy[0] * dz[1];
                s[3] += dy[1] * dz[0];
                s[4] += (dy[0] * dy[0] + dy[1] * dy[1]);
            }
        }
        a[0] = (s[0] + s[1]);
        a[1] = (s[2] - s[3]);
        if (s[4] != 0)
        {
            a[0] /= s[4];
            a[1] /= s[4];
        } else if (n > 0) {
            a[0] /= n;
            a[1] /= n;
        }
        rewind(fp0);
        dz[0] = a[0] * yc[0] - a[1] * yc[1];
        dz[1] = a[1] * yc[0] + a[0] * yc[1];
        yc[0] = dz[0];
        yc[1] = dz[1];        

        j = 0;
        sds = 0;
        while (fgets(buf, 1024, fp0) != NULL)
        {
            np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf ", name, &x[0], &x[1], &x[2], &z[0], &z[1], &z[2]);
            if (np >= 7)
            {
                if (x[0] < 0 && j < 500)
                {
                    st = 0;
                    for (i = 0; i < 3; i++)
                    {
                        z[i] -= zc[i];
                        z[i] += yc[i];
                        z[i] *= z[i];
                        st += z[i];
                    }
                    st = sqrt(st);
                    ds = st - siter[j];
                    if (ds < 0) {ds = -ds;}
                    sds += ds;
                    siter[j] = st;
                    j++;
                }
            }
        }
        k++;
        printf("Iter: %d, sum ds: %.11f\n", k, sds);
        rewind(fp0);
    }

    j = 0;
    while (fgets(buf, 1024, fp0) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf ", name, &x[0], &x[1], &x[2], &z[0], &z[1], &z[2]);
        if (np >= 7)
        {
            if (x[0] < 0)
            {
                x[0] = siter[j];
                j++;
            }
            fprintf(fp1, "%s %.4f %.8f %.8f %.4f %.4f %.4f\n", name, x[0], x[1], x[2], z[0], z[1], z[2]);
        } else {
            fprintf(fp1, "%s %.4f %.8f %.8f\n", name, x[0], x[1], x[2]);
        }
    }
    fclose(fp1);
    fclose(fp0);

    return 0;
}
