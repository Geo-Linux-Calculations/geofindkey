/*
Name: geoszbtoyxh.c
Version: 2.2
Date: 2020-09-11
Author: zvezdochiot (https://github.com/zvezdochiot)
Author: Zoltan Siki (https://github.com/zsiki)
*
build:
$ gcc -o geoszzbtoyxh geosvbtoyxh.c -lm
sample:
$ ./geoszbtoyxh doc/szb.dat yxh.dat
*
file:
input file point_id slope_distance zenith_angle bearing
doc/szb.dat:
*
OKD-4     8.605  74.08666667   234.38916667
OKD-5     8.869  81.18888889   254.73888889
OKD-K3-1  3.670  82.43944444   339.05361111
OKD-K3-4  3.690  70.66833333   161.16
OKD-K5P   3.938  71.95527778   137.52222222
OKD-K7L   4.685  83.96444444   17.82444444
OKD-K7L   4.684  276.03361111  197.82722222
OKD-K5P   3.939  288.04361111  317.52472222
OKD-K3-4  3.691  289.32972222  341.16111111
OKD-K3-1  3.671  277.55583333  159.05805556
OKD-5     8.869  278.80944444  74.74055556
OKD-4     8.604  285.91444444  54.38972222
OKD-11    3.889  71.6025       313.60777778
OKD-12    3.889  288.39138889  133.60805556
*
output file yxh.dat:
*
OKD-4 -6.7277 -4.8185 2.3593
OKD-5 -8.4553 -2.3069 1.3585
OKD-K3-1 -1.3006 3.3977 0.4829
OKD-K3-4 1.1244 -3.2954 1.2215
OKD-K5P 2.5285 -2.7616 1.2198
OKD-K7L 1.4261 4.4354 0.4926
OKD-K7L 1.4261 4.4344 0.4923
OKD-K5P 2.5291 -2.7624 1.2201
OKD-K3-4 1.1247 -3.2964 1.2217
OKD-K3-1 -1.3007 3.3987 0.4827
OKD-5 -8.4554 -2.3067 1.3583
OKD-4 -6.7269 -4.8178 2.3592
OKD-11 -2.6720 2.5452 1.2274
OKD-12 -2.6721 2.5453 1.2270
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#define PNAME "GeoSZBtoYXH"
#define PVERSION "2.2"

#define defUnits "DEG"

void geoszbtoyxhtitle()
{
    fprintf(stderr, "%s %s\n", PNAME, PVERSION);
}

void geoszbtoyxhusage()
{
    fprintf(stderr, "usage: geoszbtoyxh [option] [input-file [report-file]]\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "          -d N    decimal after comma, default=4\n");
    fprintf(stderr, "          -u str  units angles {RAD,DEG,GON,DMS}, default=DEG\n");
    fprintf(stderr, "          -h      this help\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "input-file(sample):\n");
    fprintf(stderr, " OKD-4     8.605  74.08666667   234.38916667\n");
    fprintf(stderr, " OKD-5     8.869  81.18888889   254.73888889\n");
    fprintf(stderr, " OKD-K3-1  3.670  82.43944444   339.05361111\n");
    fprintf(stderr, " OKD-K3-4  3.690  70.66833333   161.16\n");
    fprintf(stderr, " OKD-K5P   3.938  71.95527778   137.52222222\n");
    fprintf(stderr, " OKD-K7L   4.685  83.96444444   17.82444444\n");
    fprintf(stderr, " OKD-K7L   4.684  276.03361111  197.82722222\n");
    fprintf(stderr, " OKD-K5P   3.939  288.04361111  317.52472222\n");
    fprintf(stderr, " OKD-K3-4  3.691  289.32972222  341.16111111\n");
    fprintf(stderr, " OKD-K3-1  3.671  277.55583333  159.05805556\n");
    fprintf(stderr, " OKD-5     8.869  278.80944444  74.74055556\n");
    fprintf(stderr, " OKD-4     8.604  285.91444444  54.38972222\n");
    fprintf(stderr, " OKD-11    3.889  71.6025       313.60777778\n");
    fprintf(stderr, " OKD-12    3.889  288.39138889  133.60805556\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "report-file(sample):\n");
    fprintf(stderr, " OKD-4 -6.7277 -4.8185 2.3593\n");
    fprintf(stderr, " OKD-5 -8.4553 -2.3069 1.3585\n");
    fprintf(stderr, " OKD-K3-1 -1.3006 3.3977 0.4829\n");
    fprintf(stderr, " OKD-K3-4 1.1244 -3.2954 1.2215\n");
    fprintf(stderr, " OKD-K5P 2.5285 -2.7616 1.2198\n");
    fprintf(stderr, " OKD-K7L 1.4261 4.4354 0.4926\n");
    fprintf(stderr, " OKD-K7L 1.4261 4.4344 0.4923\n");
    fprintf(stderr, " OKD-K5P 2.5291 -2.7624 1.2201\n");
    fprintf(stderr, " OKD-K3-4 1.1247 -3.2964 1.2217\n");
    fprintf(stderr, " OKD-K3-1 -1.3007 3.3987 0.4827\n");
    fprintf(stderr, " OKD-5 -8.4554 -2.3067 1.3583\n");
    fprintf(stderr, " OKD-4 -6.7269 -4.8178 2.3592\n");
    fprintf(stderr, " OKD-11 -2.6720 2.5452 1.2274\n");
    fprintf(stderr, " OKD-12 -2.6721 2.5453 1.2270\n");
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
    double x[3], y[3], z[3];
    char* units;
    int np;
    FILE *fp0, *fp1;

    int opt;
    int decimals = 4;   /* number of decimals in the calculated coordinates */
    double PI2 = M_PI / 2.0;  /* PI/2 */
    int fhelp = 0;  /* default no help*/
    units = defUnits;
    while ((opt = getopt(argc, argv, "d:u:h")) != -1)
    {
        switch(opt)
        {
            case 'h':
                fhelp = 1;
                break;
            case 'd':
                decimals = atoi(optarg);
                break;
            case 'u':
                units = optarg;
                break;
            case ':':
                fprintf(stderr, "option needs a value\n");
                fhelp = 1;
                break;
            case '?':
                fprintf(stderr, "unknown option: %c\n", optopt);
                fhelp = 1;
                break;
        }
    }

    sprintf(format4, "%%s %%.%df %%.%df %%.%df\n",
        decimals, decimals, decimals);
    sprintf(format7, "%%s %%.%df %%.%df %%.%df %%.%df %%.%df %%.%df 1\n",
        decimals, decimals, decimals, decimals, decimals, decimals);
    geoszbtoyxhtitle();

    if (fhelp)
    {
        geoszbtoyxhusage();
        exit(0);
    }

    if (argc > optind)
    {
        if ((fp0 = fopen(argv[optind], "r")) == NULL)
        {
            fprintf(stderr, "can't open %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    } else {
        fp0 = stdin;    /* use standard input if no file given */
    }
    if (argc > optind+1)
    {
        if ((fp1 = fopen(argv[optind + 1], "w")) == NULL)
        {
            fprintf(stderr, "can't create %s\n", argv[2]);
            exit(EXIT_FAILURE);
        }
    } else {
        fp1 = stdout;   /* use standard output if no file given */
    }

    while (fgets(buf, 1024, fp0) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf",
            name, &x[0], &x[1], &x[2], &z[0], &z[1], &z[2]);
        if (np >= 4) {
            x[1] = ANGLEtoRAD(x[1], units);
            x[1] = PI2 - x[1];;
            x[2] = ANGLEtoRAD(x[2], units);
            y[2] = x[0] * sin(x[1]);
            x[0] *= cos(x[1]);
            y[0] = x[0] * sin(x[2]);
            y[1] = x[0] * cos(x[2]);
            if (np >= 7)
            {
                fprintf(fp1, format7, name, y[0], y[1], y[2], z[0], z[1], z[2]);
            } else {
                fprintf(fp1, format4, name, y[0], y[1], y[2]);
            }
        } else {
            if (np > 0) {       /* no error for empty lines */
                fprintf(stderr, "Error in input, lines kipped: \n%s\n", buf);
            }
        }
    }
    fclose(fp1);
    fclose(fp0);

    return 0;
}
