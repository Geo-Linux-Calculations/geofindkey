/*
Name: geoszbtoyxh.c
Version: 1.6
Date: 2018-05-26
Author: zvezdochiot (https://github.com/zvezdochiot)
*
build:
$ gcc -o geoszzbtoyxh geosvbtoyxh.c -lm
sample:
$ ./geoszbtoyxh doc/szb.dat yxh.dat
*
file:
input file doc/szb.dat:
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

#define PNAME "GeoSZBtoYXH"
#define PVERSION "1.6"

void geoszbtoyxhtitle()
{
    printf("%s %s\n", PNAME, PVERSION);
}

void geoszbtoyxhusage()
{
    printf("usage: geoszbtoyxh [option] input-file report-file\n");
    printf("options:\n");
    printf("          -h      this help\n");
    printf("\n");
    printf("input-file(sample):\n");
    printf(" OKD-4     8.605  74.08666667   234.38916667\n");
    printf(" OKD-5     8.869  81.18888889   254.73888889\n");
    printf(" OKD-K3-1  3.670  82.43944444   339.05361111\n");
    printf(" OKD-K3-4  3.690  70.66833333   161.16\n");
    printf(" OKD-K5P   3.938  71.95527778   137.52222222\n");
    printf(" OKD-K7L   4.685  83.96444444   17.82444444\n");
    printf(" OKD-K7L   4.684  276.03361111  197.82722222\n");
    printf(" OKD-K5P   3.939  288.04361111  317.52472222\n");
    printf(" OKD-K3-4  3.691  289.32972222  341.16111111\n");
    printf(" OKD-K3-1  3.671  277.55583333  159.05805556\n");
    printf(" OKD-5     8.869  278.80944444  74.74055556\n");
    printf(" OKD-4     8.604  285.91444444  54.38972222\n");
    printf(" OKD-11    3.889  71.6025       313.60777778\n");
    printf(" OKD-12    3.889  288.39138889  133.60805556\n");
    printf("\n");
    printf("report-file(sample):\n");
    printf(" OKD-4 -6.7277 -4.8185 2.3593\n");
    printf(" OKD-5 -8.4553 -2.3069 1.3585\n");
    printf(" OKD-K3-1 -1.3006 3.3977 0.4829\n");
    printf(" OKD-K3-4 1.1244 -3.2954 1.2215\n");
    printf(" OKD-K5P 2.5285 -2.7616 1.2198\n");
    printf(" OKD-K7L 1.4261 4.4354 0.4926\n");
    printf(" OKD-K7L 1.4261 4.4344 0.4923\n");
    printf(" OKD-K5P 2.5291 -2.7624 1.2201\n");
    printf(" OKD-K3-4 1.1247 -3.2964 1.2217\n");
    printf(" OKD-K3-1 -1.3007 3.3987 0.4827\n");
    printf(" OKD-5 -8.4554 -2.3067 1.3583\n");
    printf(" OKD-4 -6.7269 -4.8178 2.3592\n");
    printf(" OKD-11 -2.6720 2.5452 1.2274\n");
    printf(" OKD-12 -2.6721 2.5453 1.2270\n");
}

int main(int argc, char *argv[])
{
    char buf[1024], name[32];
    double x[3], y[3], z[3];
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
                printf("option needs a value\n");
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                break;
        }
    }

    geoszbtoyxhtitle();

    if ((optind + 2 > argc) || (fhelp > 0))
    {
        geoszbtoyxhusage();
        exit(0);
    }

    if ((fp0 = fopen(argv[optind], "r")) == NULL)
    {
        printf("can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ((fp1 = fopen(argv[optind + 1], "w")) == NULL)
    {
        printf("can't create %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    while (fgets(buf, 1024, fp0) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf ", name, &x[0], &x[1], &x[2], &z[0], &z[1], &z[2]);
        x[1] = 90 - x[1];;
        x[1] *= M_PI;
        x[1] /= 180.0;
        x[2] *= M_PI;
        x[2] /= 180.0;
        y[2] = x[0] * sin(x[1]);
        x[0] *= cos(x[1]);
        y[0] = x[0] * sin(x[2]);
        y[1] = x[0] * cos(x[2]);
        if (np >= 7)
        {
            fprintf(fp1, "%s %.4f %.4f %.4f %.4f %.4f %.4f 1\n", name, y[0], y[1], y[2], z[0], z[1], z[2]);
        } else {
            fprintf(fp1, "%s %.4f %.4f %.4f\n", name, y[0], y[1], y[2]);
        }
    }
    fclose(fp1);
    fclose(fp0);

    return 0;
}
