/*
Name: geositer500.c
Version: 3.1
Date: 2021-12-30
Author: zvezdochiot (https://github.com/zvezdochiot)
Author: Zoltan Siki (https://github.com/zsiki)
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

#include "geofindkey.h"

#define PNAME "GeoSIter500"

void geositer500title()
{
    fprintf(stderr, "%s %s\n", PNAME, PVERSION);
}

void geositer500usage()
{
    fprintf(stderr, "usage: geositer500 [option] input-file report-file\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "          -a N.N  atmospheric refractive index, default=%g\n", defKAtm);
    fprintf(stderr, "          -d N    decimal after comma, default=%d\n", defDecimals);
    fprintf(stderr, "          -r N.N  radius Earth, default=%g\n", defREarth);
    fprintf(stderr, "          -u str  units angles {RAD,DEG,GON,DMS}, default=%s\n", defUnits);
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

double DEGtoRAD(double val)
{
    static double d2r = M_PI / 180.0;  /* degree to radians factor */
    val *= d2r;
    return val;
}
double GONtoRAD(double val)
{
    static double g2r = M_PI / 200.0;  /* gon to radians factor */
    val *= g2r;
    return val;
}
double DMStoDEG(double val)
{
    double D, M, S;
    D = (int)val;
    M = (int)((val - D) * 100.0);
    S = ((val - D) * 100.0 - M) * 100.0;
    val = D + (M + S / 60.0) / 60.0;
    return val;
}
double ANGLEtoRAD(double val, char* units)
{
    if (!strcmp(units,"RAD"))
        return val;
    if (!strcmp(units,"DEG"))
        return DEGtoRAD(val);
    if (!strcmp(units,"DMS"))
        return DEGtoRAD(DMStoDEG(val));
    if (!strcmp(units,"GON"))
        return GONtoRAD(val);
    return val;
}

int main(int argc, char *argv[])
{
    char buf[1024], name[32], format4[128], format7[128];
    double x[3], y[3], z[3], dy[3], dz[3], s[6], a[2];
    double yc[3], zc[3];
    double siter[500], st, ds, sds, thres;
    unsigned n, i, j, k;
    char* units;
    int np;
    FILE *fpin, *fpout;

    int opt;
    int decimals = defDecimals;   /* number of decimals in the calculated coordinates */
    double atmospheric = defKAtm, RE = defREarth;
    int fhelp = 0;
    units = defUnits;
    while ((opt = getopt(argc, argv, "a:d:r:u:h")) != -1)
    {
        switch(opt)
        {
        case 'a':
            atmospheric = atof(optarg);
            break;
        case 'd':
            decimals = atoi(optarg);
            break;
        case 'h':
            fhelp = 1;
            break;
        case 'r':
            RE = atof(optarg);
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

    sprintf(format4, "%%s %%.%df %%.8f %%.8f\n",
            decimals);
    sprintf(format7, "%%s %%.%df %%.8f %%.8f %%.%df %%.%df %%.%df\n",
            decimals, decimals, decimals, decimals);
    geositer500title();

    if ((optind + 2 > argc) || (fhelp > 0))
    {
        geositer500usage();
        exit(0);
    }

    if ((fpin = fopen(argv[optind], "r")) == NULL)
    {
        fprintf(stderr, "can't open %s\n", argv[optind]);
        exit(EXIT_FAILURE);
    }
    if ((fpout = fopen(argv[optind + 1], "w")) == NULL)
    {
        fprintf(stderr, "can't create %s\n", argv[optind + 1]);
        exit(EXIT_FAILURE);
    }

    n = 0;
    for (j = 0; j < 500; j++)
    {
        siter[j] = 1.0;
    }
    while (fgets(buf, 1024, fpin) != NULL)
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
    rewind(fpin);

    printf("Unknow distance: %d\n", n);
    thres = 1.0;
    sds = 0.0;
    k = 0;
    while (sds < thres)
    {
        thres = sds;
        for (i = 0; i < 3; i++)
        {
            yc[i] = 0;
            zc[i] = 0;
        }
        n = 0;
        j = 0;
        while (fgets(buf, 1024, fpin) != NULL)
        {
            np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf ", name, &x[0], &x[1], &x[2], &z[0], &z[1], &z[2]);
            if (np >= 7)
            {
                if (x[0] < 0 && j < 500)
                {
                    x[0] = siter[j];
                    j++;
                }
                x[1] = ANGLEtoRAD(x[1], units);
                x[1] -= (RE > 0.0) ? (x[0] * sin(x[1]) * 0.5 / RE * (1.0 - atmospheric)) : 0.0;
                x[2] = ANGLEtoRAD(x[2], units);
                y[2] = x[0] * cos(x[1]);
                x[0] *= sin(x[1]);
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
        rewind(fpin);

        for (i = 0; i < 6; i++)
        {
            s[i] = 0;
        }
        j = 0;
        while (fgets(buf, 1024, fpin) != NULL)
        {
            np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf ", name, &x[0], &x[1], &x[2], &z[0], &z[1], &z[2]);
            if (np >= 7)
            {
                if (x[0] < 0 && j < 500)
                {
                    x[0] = siter[j];
                    j++;
                }
                x[1] = ANGLEtoRAD(x[1], units);
                x[1] -= (RE > 0.0) ? (x[0] * sin(x[1]) * 0.5 / RE * (1.0 - atmospheric)) : 0.0;
                x[2] = ANGLEtoRAD(x[2], units);
                y[2] = x[0] * cos(x[1]);
                x[0] *= sin(x[1]);
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
        }
        else if (n > 0)
        {
            a[0] /= n;
            a[1] /= n;
        }
        rewind(fpin);
        dz[0] = a[0] * yc[0] - a[1] * yc[1];
        dz[1] = a[1] * yc[0] + a[0] * yc[1];
        yc[0] = dz[0];
        yc[1] = dz[1];

        j = 0;
        sds = 0;
        while (fgets(buf, 1024, fpin) != NULL)
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
                    if (ds < 0)
                    {
                        ds = -ds;
                    }
                    sds += ds;
                    siter[j] = st;
                    j++;
                }
            }
        }
        k++;
        printf("Iter: %d, sum ds: %.11f\n", k, sds);
        rewind(fpin);
        thres = (thres > 0.0) ? thres : (sds * 2.0);
    }

    j = 0;
    while (fgets(buf, 1024, fpin) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf ", name, &x[0], &x[1], &x[2], &z[0], &z[1], &z[2]);
        if (np >= 4)
        {
            if (np >= 7)
            {
                if (x[0] < 0)
                {
                    x[0] = siter[j];
                    j++;
                }
                fprintf(fpout, format7, name, x[0], x[1], x[2], z[0], z[1], z[2]);
            }
            else
            {
                fprintf(fpout, format4, name, x[0], x[1], x[2]);
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
    fclose(fpout);
    fclose(fpin);

    return 0;
}
