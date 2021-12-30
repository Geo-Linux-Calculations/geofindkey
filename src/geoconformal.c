/*
Name: geoconformal.c
(use Gauss normalize @zvezdochiot[https://geodesist.ru/members/zvezdochiot.47244/])
(use PQ-scheme by Alexander Starostin aka @stout[https://geodesist.ru/members/stout.228/])
(use Last published version of CCMATH by Daniel Atkinson in 2001 (version 2.2.1)[https://github.com/mnhrdt/ccmath].)
(use Gnumeric OLS spreadsheets [https://github.com/Geo-Linux-Calculations/gnumeric-ols])
Version: 3.1
Date: 2021-12-30
Author: zvezdochiot (https://github.com/zvezdochiot)
*
build:
$ gcc -o geoconformal geoconformal.c -lm
sample:
$ ./geoconformal -p 5 doc/data2.dat report.dat
*
file:
input file doc/data2.dat:
*
N-030E-030 4401251.530614 385234.157603 1.0000  6179000 626000 11.0000 1.0000
N-020E-020 4410870.677752 395053.144641 2.0000  6189000 636000 12.0000 1.0000
N-020E+020 4410435.860319 433933.803034 3.0000  6189000 676000 13.0000 1.0000
N-015E-015 4415680.047375 399965.233324 4.0000  6194000 641000 14.0000 1.0000
N-015E+015 4415353.577891 429130.894381 5.0000  6194000 671000 15.0000 1.0000
N-005E-005 4425298.398598 409794.581471 6.0000  6204000 651000 16.0000 1.0000
N-005E+005 4425189.337943 419519.905407 7.0000  6204000 661000 17.0000 1.0000
N+000E+000 4430107.388185 414711.833121 8.0000  6209000 656000 18.0000 1.0000
N+005E-005 4435025.557099 409902.047661 9.0000  6214000 651000 19.0000 1.0000
N+005E+005 4434916.259102 419630.797946 10.0000 6214000 661000 20.0000 1.0000
N+015E-015 4444862.266609 400277.353296 11.0000 6224000 641000 21.0000 1.0000
N+015E+015 4444533.661039 429473.851498 12.0000 6224000 671000 22.0000 1.0000
N+020E-020 4449780.815068 395462.452433 13.0000 6229000 636000 23.0000 1.0000
N+020E+020 4449342.200149 434397.932415 14.0000 6229000 676000 24.0000 1.0000
N+030E+030 4458958.974978 444251.183014 15.0000 6239000 686000 25.0000 1.0000
N-030E+030 4400600.730781 443534.428587 16.0000
N-025E-025 4406061.173485 390142.784765 17.0000
N-025E+025 4405518.245899 438734.982441 18.0000
N-010E-010 4420489.286328 404879.046903 19.0000
N-010E+010 4420271.402474 424326.260500 20.0000
N+010E-010 4439943.848599 405090.553046 21.0000
N+010E+010 4439725.015373 424551.472040 22.0000
N+025E-025 4454699.497928 390645.854478 23.0000
N+025E+025 4454150.636770 439323.710888 24.0000
N+030E-030 4459618.319154 385827.563453 25.0000
*
output file report.dat:
*
Power: 5
Mean: 15
M 4430107.1035 414715.9447 8.0000 6209000.0000 656000.0000 18.0000
NORM = 4.2442e-05, 4.2442e-05, 0.163663
cond(G) = 344.167
Place (X,Y):
key(0):
 --0--:
 6208999.7548
 656004.2298
 --1--:
 1.02793265322
 -0.0115379918737
 --2--:
 -1.86441957028e-08
 -6.61875925805e-10
 --3--:
 3.62997666575e-15
 -3.50555995009e-17
 --4--:
 -5.10244217007e-23
 -6.75852311145e-24
 --5--:
 1.71236306923e-28
 2.34991032411e-27
Decentralize:
key:
 --0--:
 2541558.8451
 -3690045.9985
 --1--:
 0.0541190506137
 4.4654307921
 --2--:
 3.54407510072e-07
 -2.03772176325e-06
 --3--:
 -4.85117887654e-14
 4.63609637196e-13
 --4--:
 1.0287260806e-21
 -5.24136027545e-20
 --5--:
 1.71236306923e-28
 2.34991032411e-27

Elevation (H):
key:
 --0--:
 10.0000
 --1--:
 1

var:
N-030E-030 4401251.5306 385234.1576 1.0000 6179000.0000 626000.0000 11.0000 1 +0.0000 -0.0000 +0.0000
N-020E-020 4410870.6778 395053.1446 2.0000 6189000.0000 636000.0000 12.0000 1 -0.0000 +0.0000 +0.0000
N-020E+020 4410435.8603 433933.8030 3.0000 6189000.0000 676000.0000 13.0000 1 +0.0000 +0.0000 +0.0000
N-015E-015 4415680.0474 399965.2333 4.0000 6194000.0000 641000.0000 14.0000 1 -0.0000 +0.0000 +0.0000
N-015E+015 4415353.5779 429130.8944 5.0000 6194000.0000 671000.0000 15.0000 1 -0.0000 -0.0000 +0.0000
N-005E-005 4425298.3986 409794.5815 6.0000 6204000.0000 651000.0000 16.0000 1 -0.0000 +0.0000 +0.0000
N-005E+005 4425189.3379 419519.9054 7.0000 6204000.0000 661000.0000 17.0000 1 -0.0000 -0.0000 +0.0000
N+000E+000 4430107.3882 414711.8331 8.0000 6209000.0000 656000.0000 18.0000 1 +0.0000 -0.0000 +0.0000
N+005E-005 4435025.5571 409902.0477 9.0000 6214000.0000 651000.0000 19.0000 1 +0.0000 +0.0000 +0.0000
N+005E+005 4434916.2591 419630.7979 10.0000 6214000.0000 661000.0000 20.0000 1 +0.0000 -0.0000 +0.0000
N+015E-015 4444862.2666 400277.3533 11.0000 6224000.0000 641000.0000 21.0000 1 +0.0000 +0.0000 +0.0000
N+015E+015 4444533.6610 429473.8515 12.0000 6224000.0000 671000.0000 22.0000 1 +0.0000 -0.0000 +0.0000
N+020E-020 4449780.8151 395462.4524 13.0000 6229000.0000 636000.0000 23.0000 1 -0.0000 -0.0000 +0.0000
N+020E+020 4449342.2001 434397.9324 14.0000 6229000.0000 676000.0000 24.0000 1 -0.0000 -0.0000 +0.0000
N+030E+030 4458958.9750 444251.1830 15.0000 6239000.0000 686000.0000 25.0000 1 -0.0000 +0.0000 +0.0000
N-030E+030 4400600.7308 443534.4286 16.0000 6179000.0003 686000.0003 26.0000
N-025E-025 4406061.1735 390142.7848 17.0000 6184000.0000 631000.0000 27.0000
N-025E+025 4405518.2459 438734.9824 18.0000 6184000.0001 681000.0001 28.0000
N-010E-010 4420489.2863 404879.0469 19.0000 6199000.0000 646000.0000 29.0000
N-010E+010 4420271.4025 424326.2605 20.0000 6199000.0000 666000.0000 30.0000
N+010E-010 4439943.8486 405090.5530 21.0000 6219000.0000 646000.0000 31.0000
N+010E+010 4439725.0154 424551.4720 22.0000 6219000.0000 666000.0000 32.0000
N+025E-025 4454699.4979 390645.8545 23.0000 6233999.9999 630999.9999 33.0000
N+025E+025 4454150.6368 439323.7109 24.0000 6234000.0000 681000.0000 34.0000
N+030E-030 4459618.3192 385827.5635 25.0000 6238999.9997 625999.9997 35.0000

diff:
0.0000 0.0000 0.0000
*
*/

#include "geofindkey.h"

#define PNAME "GeoConformal"

void geoconformaltitle()
{
    fprintf(stderr, "%s %s\n", PNAME, PVERSION);
}

void geoconformalusage()
{
    fprintf(stderr, "usage: geoconformal [option] input-file report-file\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "          -d N    decimal after comma, default=%d\n", defDecimals);
    fprintf(stderr, "          -p N    power transform, {0..%d}, default=%d (npoint-1)\n", maxPOW, defPOW);
    fprintf(stderr, "          -h      this help\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "input-file(sample):\n");
    fprintf(stderr, " N-030E-030 4401251.530614 385234.157603 1.0000  6179000 626000 11.0000 1.0000\n");
    fprintf(stderr, " N-020E-020 4410870.677752 395053.144641 2.0000  6189000 636000 12.0000 1.0000\n");
    fprintf(stderr, " N-020E+020 4410435.860319 433933.803034 3.0000  6189000 676000 13.0000 1.0000\n");
    fprintf(stderr, " N-015E-015 4415680.047375 399965.233324 4.0000  6194000 641000 14.0000 1.0000\n");
    fprintf(stderr, " N-015E+015 4415353.577891 429130.894381 5.0000  6194000 671000 15.0000 1.0000\n");
    fprintf(stderr, " N-005E-005 4425298.398598 409794.581471 6.0000  6204000 651000 16.0000 1.0000\n");
    fprintf(stderr, " N-005E+005 4425189.337943 419519.905407 7.0000  6204000 661000 17.0000 1.0000\n");
    fprintf(stderr, " N+000E+000 4430107.388185 414711.833121 8.0000  6209000 656000 18.0000 1.0000\n");
    fprintf(stderr, " N+005E-005 4435025.557099 409902.047661 9.0000  6214000 651000 19.0000 1.0000\n");
    fprintf(stderr, " N+005E+005 4434916.259102 419630.797946 10.0000 6214000 661000 20.0000 1.0000\n");
    fprintf(stderr, " N+015E-015 4444862.266609 400277.353296 11.0000 6224000 641000 21.0000 1.0000\n");
    fprintf(stderr, " N+015E+015 4444533.661039 429473.851498 12.0000 6224000 671000 22.0000 1.0000\n");
    fprintf(stderr, " N+020E-020 4449780.815068 395462.452433 13.0000 6229000 636000 23.0000 1.0000\n");
    fprintf(stderr, " N+020E+020 4449342.200149 434397.932415 14.0000 6229000 676000 24.0000 1.0000\n");
    fprintf(stderr, " N+030E+030 4458958.974978 444251.183014 15.0000 6239000 686000 25.0000 1.0000\n");
    fprintf(stderr, " N-030E+030 4400600.730781 443534.428587 16.0000\n");
    fprintf(stderr, " N-025E-025 4406061.173485 390142.784765 17.0000\n");
    fprintf(stderr, " N-025E+025 4405518.245899 438734.982441 18.0000\n");
    fprintf(stderr, " N-010E-010 4420489.286328 404879.046903 19.0000\n");
    fprintf(stderr, " N-010E+010 4420271.402474 424326.260500 20.0000\n");
    fprintf(stderr, " N+010E-010 4439943.848599 405090.553046 21.0000\n");
    fprintf(stderr, " N+010E+010 4439725.015373 424551.472040 22.0000\n");
    fprintf(stderr, " N+025E-025 4454699.497928 390645.854478 23.0000\n");
    fprintf(stderr, " N+025E+025 4454150.636770 439323.710888 24.0000\n");
    fprintf(stderr, " N+030E-030 4459618.319154 385827.563453 25.0000\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "report-file(sample):\n");
    fprintf(stderr, " Power: 5\n");
    fprintf(stderr, " Mean: 15\n");
    fprintf(stderr, " M 4430107.1035 414715.9447 8.0000 6209000.0000 656000.0000 18.0000\n");
    fprintf(stderr, " NORM = 4.2442e-05, 4.2442e-05, 0.163663\n");
    fprintf(stderr, " cond(G) = 344.167\n");
    fprintf(stderr, " Place (X,Y):\n");
    fprintf(stderr, " key(0):\n");
    fprintf(stderr, "  --0--:\n");
    fprintf(stderr, "  6208999.7548\n");
    fprintf(stderr, "  656004.2298\n");
    fprintf(stderr, "  --1--:\n");
    fprintf(stderr, "  1.02793265322\n");
    fprintf(stderr, "  -0.0115379918737\n");
    fprintf(stderr, "  --2--:\n");
    fprintf(stderr, "  -1.86441957028e-08\n");
    fprintf(stderr, "  -6.61875925805e-10\n");
    fprintf(stderr, "  --3--:\n");
    fprintf(stderr, "  3.62997666575e-15\n");
    fprintf(stderr, "  -3.50555995009e-17\n");
    fprintf(stderr, "  --4--:\n");
    fprintf(stderr, "  -5.10244217007e-23\n");
    fprintf(stderr, "  -6.75852311145e-24\n");
    fprintf(stderr, "  --5--:\n");
    fprintf(stderr, "  1.71236306923e-28\n");
    fprintf(stderr, "  2.34991032411e-27\n");
    fprintf(stderr, " Decentralize:\n");
    fprintf(stderr, " key:\n");
    fprintf(stderr, "  --0--:\n");
    fprintf(stderr, "  2541558.8451\n");
    fprintf(stderr, "  -3690045.9985\n");
    fprintf(stderr, "  --1--:\n");
    fprintf(stderr, "  0.0541190506137\n");
    fprintf(stderr, "  4.4654307921\n");
    fprintf(stderr, "  --2--:\n");
    fprintf(stderr, "  3.54407510072e-07\n");
    fprintf(stderr, "  -2.03772176325e-06\n");
    fprintf(stderr, "  --3--:\n");
    fprintf(stderr, "  -4.85117887654e-14\n");
    fprintf(stderr, "  4.63609637196e-13\n");
    fprintf(stderr, "  --4--:\n");
    fprintf(stderr, "  1.0287260806e-21\n");
    fprintf(stderr, "  -5.24136027545e-20\n");
    fprintf(stderr, "  --5--:\n");
    fprintf(stderr, "  1.71236306923e-28\n");
    fprintf(stderr, "  2.34991032411e-27\n");
    fprintf(stderr, " \n");
    fprintf(stderr, " Elevation (H):\n");
    fprintf(stderr, " key:\n");
    fprintf(stderr, "  --0--:\n");
    fprintf(stderr, "  10.0000\n");
    fprintf(stderr, "  --1--:\n");
    fprintf(stderr, "  1\n");
    fprintf(stderr, " \n");
    fprintf(stderr, " var:\n");
    fprintf(stderr, " N-030E-030 4401251.5306 385234.1576 1.0000 6179000.0000 626000.0000 11.0000 1 +0.0000 -0.0000 +0.0000\n");
    fprintf(stderr, " N-020E-020 4410870.6778 395053.1446 2.0000 6189000.0000 636000.0000 12.0000 1 -0.0000 +0.0000 +0.0000\n");
    fprintf(stderr, " N-020E+020 4410435.8603 433933.8030 3.0000 6189000.0000 676000.0000 13.0000 1 +0.0000 +0.0000 +0.0000\n");
    fprintf(stderr, " N-015E-015 4415680.0474 399965.2333 4.0000 6194000.0000 641000.0000 14.0000 1 -0.0000 +0.0000 +0.0000\n");
    fprintf(stderr, " N-015E+015 4415353.5779 429130.8944 5.0000 6194000.0000 671000.0000 15.0000 1 -0.0000 -0.0000 +0.0000\n");
    fprintf(stderr, " N-005E-005 4425298.3986 409794.5815 6.0000 6204000.0000 651000.0000 16.0000 1 -0.0000 +0.0000 +0.0000\n");
    fprintf(stderr, " N-005E+005 4425189.3379 419519.9054 7.0000 6204000.0000 661000.0000 17.0000 1 -0.0000 -0.0000 +0.0000\n");
    fprintf(stderr, " N+000E+000 4430107.3882 414711.8331 8.0000 6209000.0000 656000.0000 18.0000 1 +0.0000 -0.0000 +0.0000\n");
    fprintf(stderr, " N+005E-005 4435025.5571 409902.0477 9.0000 6214000.0000 651000.0000 19.0000 1 +0.0000 +0.0000 +0.0000\n");
    fprintf(stderr, " N+005E+005 4434916.2591 419630.7979 10.0000 6214000.0000 661000.0000 20.0000 1 +0.0000 -0.0000 +0.0000\n");
    fprintf(stderr, " N+015E-015 4444862.2666 400277.3533 11.0000 6224000.0000 641000.0000 21.0000 1 +0.0000 +0.0000 +0.0000\n");
    fprintf(stderr, " N+015E+015 4444533.6610 429473.8515 12.0000 6224000.0000 671000.0000 22.0000 1 +0.0000 -0.0000 +0.0000\n");
    fprintf(stderr, " N+020E-020 4449780.8151 395462.4524 13.0000 6229000.0000 636000.0000 23.0000 1 -0.0000 -0.0000 +0.0000\n");
    fprintf(stderr, " N+020E+020 4449342.2001 434397.9324 14.0000 6229000.0000 676000.0000 24.0000 1 -0.0000 -0.0000 +0.0000\n");
    fprintf(stderr, " N+030E+030 4458958.9750 444251.1830 15.0000 6239000.0000 686000.0000 25.0000 1 -0.0000 +0.0000 +0.0000\n");
    fprintf(stderr, " N-030E+030 4400600.7308 443534.4286 16.0000 6179000.0003 686000.0003 26.0000\n");
    fprintf(stderr, " N-025E-025 4406061.1735 390142.7848 17.0000 6184000.0000 631000.0000 27.0000\n");
    fprintf(stderr, " N-025E+025 4405518.2459 438734.9824 18.0000 6184000.0001 681000.0001 28.0000\n");
    fprintf(stderr, " N-010E-010 4420489.2863 404879.0469 19.0000 6199000.0000 646000.0000 29.0000\n");
    fprintf(stderr, " N-010E+010 4420271.4025 424326.2605 20.0000 6199000.0000 666000.0000 30.0000\n");
    fprintf(stderr, " N+010E-010 4439943.8486 405090.5530 21.0000 6219000.0000 646000.0000 31.0000\n");
    fprintf(stderr, " N+010E+010 4439725.0154 424551.4720 22.0000 6219000.0000 666000.0000 32.0000\n");
    fprintf(stderr, " N+025E-025 4454699.4979 390645.8545 23.0000 6233999.9999 630999.9999 33.0000\n");
    fprintf(stderr, " N+025E+025 4454150.6368 439323.7109 24.0000 6234000.0000 681000.0000 34.0000\n");
    fprintf(stderr, " N+030E-030 4459618.3192 385827.5635 25.0000 6238999.9997 625999.9997 35.0000\n");
    fprintf(stderr, " \n");
    fprintf(stderr, " diff:\n");
    fprintf(stderr, " 0.0000 0.0000 0.0000\n");
}

int main(int argc, char *argv[])
{
    char buf[1024], name[128], format1[128], format3[128], format7[128], format11[128];
    double x[3], y[3], z[3], xcp[3], ycp[3], xs[3], dz[3], wgt, wgts, n, gnorm[3];
    double *pq, *gmat, *gvec, *gparam, *aparam, eparam[2], condg, t;
    unsigned i, j, k, l, m;
    int np, *dck;
    FILE *fpin, *fpout;

    int opt;
    int decimals = defDecimals;   /* number of decimals in the calculated coordinates */
    int npow = defPOW;   /* power transformstion */
    int fhelp = 0;

    while ((opt = getopt(argc, argv, "d:p:h")) != -1)
    {
        switch(opt)
        {
        case 'd':
            decimals = atoi(optarg);
            break;
        case 'h':
            fhelp = 1;
            break;
        case 'p':
            npow = atoi(optarg);
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
    geoconformaltitle();

    if ((optind + 2 > argc) || (fhelp > 0))
    {
        geoconformalusage();
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
        npow = ((npow > (int)(n - 1)) || (npow < 0)) ? (n - 1) : npow;
        npow = (npow > maxPOW) ? maxPOW : npow;
        fprintf(fpout, "Power: %d\n", npow);
        npow++;

        pq = (double *)malloc(2 * npow * sizeof(double));
        gmat = (double *)malloc(4 * npow * npow * sizeof(double));
        gvec = (double *)malloc(2 * npow * sizeof(double));
        gparam = (double *)malloc(2 * npow * sizeof(double));
        aparam = (double *)malloc(2 * npow * sizeof(double));
        dck = (int *)malloc(2 * npow * sizeof(int));

        n = (wgts > 0.0) ? wgts : n;
        for (j = 0; j < 3; j++)
        {
            xcp[j] /= n;
            ycp[j] /= n;
            xs[j] /= n;
            xs[j] -= (xcp[j] * xcp[j]);
        }
        gnorm[0] = xs[0] + xs[1];
        gnorm[0] = (gnorm[0] > 0) ? (1.0 / sqrt(gnorm[0])) : 1.0;
        gnorm[1] = gnorm[0];
        gnorm[2] = xs[2] * 2.0;
        gnorm[2] = (gnorm[2] > 0) ? (1.0 / sqrt(gnorm[2])) : 1.0;
        fprintf(fpout, "Mean: %g\n", n);
        fprintf(fpout, format7, "M", xcp[0], xcp[1], xcp[2], ycp[0], ycp[1], ycp[2]);
        fprintf(fpout, "NORM = %g, %g, %g\n", gnorm[0], gnorm[1], gnorm[2]);
        rewind(fpin);

        for (j = 0; j < 4 * npow * npow; j++)
        {
            gmat[j] = 0.0;
        }
        for (j = 0; j < 2 * npow; j++)
        {
            gvec[j] = 0.0;
            gparam[j] = 0.0;
            aparam[j] = 0.0;
            pq[j] = 0.0;
            dck[j] = 0;
        }
        for (j = 0; j < 3; j++)
        {
            xs[j] = 0.0;
        }
        eparam[0] = 0.0;
        eparam[1] = 0.0;
        while (fgets(buf, 1024, fpin) != NULL)
        {
            np = sscanf(buf, "%s %lf %lf %lf %lf %lf %lf %lf", name, &x[0], &x[1], &x[2], &y[0], &y[1], &y[2], &wgt);
            if (np >= 8)
            {
                for (i = 0; i < 3; i++)
                {
                    x[i] = gaussnorm(x[i], xcp[i], gnorm[i]);
                    xs[i] = (x[i] * x[i] * wgt);
                    y[i] = gaussnorm(y[i], ycp[i], gnorm[i]);
                }
                eparam[0] += (x[2] * x[2] * wgt);
                eparam[1] += (x[2] * y[2] * wgt);
                /* PQ-scheme by Alexander Starostin aka @stout */
                pq[0] = 1.0;
                pq[npow] = 0.0;
                for (i = 1; i < npow; i++)
                {
                    j = i + npow;
                    pq[i] = pq[i - 1] * x[0] - pq[j - 1] * x[1];
                    pq[j] = pq[i - 1] * x[1] + pq[j - 1] * x[0];
                }
                for (i = 0; i < npow; i++)
                {
                    k = 2 * i;
                    for (j = 0; j < npow; j++)
                    {
                        l = 2 * j;
                        m = 2 * k * npow + l;
                        gmat[m] += (pq[i] * pq[j] + pq[i + npow] * pq[j + npow]) * wgt;
                        gmat[m + 1] += (pq[i + npow] * pq[j] - pq[i] * pq[j + npow]) * wgt;
                        gmat[m + npow + npow] = -gmat[m + 1];
                        gmat[m + npow + npow + 1] = gmat[m];
                    }
                    gvec[k] += (pq[i] * y[0] + pq[i + npow] * y[1]) * wgt;
                    gvec[k + 1] += (pq[i] * y[1] - pq[i + npow] * y[0]) * wgt;;
                }
            }
        }
        condg = minv(gmat, 2 * npow);
        fprintf(fpout, "cond(G) = %g\n", condg);
        rewind(fpin);

        if (condg > 0.0)
        {
            fprintf(fpout, "Place (X,Y):\n");
            for (i = 0; i < 2 * npow; i++)
            {
                gparam[i] = 0.0;
                for (j = 0; j < 2 * npow; j++)
                {
                    m = 2 * i * npow + j;
                    gparam[i] += gmat[m] * gvec[j];
                }
            }
            t = 1.0 / gnorm[0];
            for (i = 0; i < npow; i++)
            {
                j = 2 * i;
                gparam[j] *= t;
                gparam[j + 1] *= t;
                t *= gnorm[0];
            }
            gparam[0] += ycp[0];
            gparam[1] += ycp[1];
            fprintf(fpout, "key(0):\n");
            fprintf(fpout, " --0--:\n");
            fprintf(fpout, format1, gparam[0]);
            fprintf(fpout, format1, gparam[1]);
            for (i = 1; i < npow; i++)
            {
                fprintf(fpout, " --%d--:\n", i);
                j = 2 * i;
                fprintf(fpout, " %.12g\n", gparam[j]);
                fprintf(fpout, " %.12g\n", gparam[j + 1]);
            }
            /* Decentralize params */
            fprintf(fpout, "Decentralize:\n");
            /* PQ-scheme by Alexander Starostin aka @stout */
            pq[0] = 1.0;
            pq[npow] = 0.0;
            dck[0] = 1;
            dck[npow] = 1;
            for (i = 1; i < npow; i++)
            {
                j = i + npow;
                pq[i] = pq[i - 1] * xcp[0] - pq[j - 1] * xcp[1];
                pq[j] = pq[i - 1] * xcp[1] + pq[j - 1] * xcp[0];
                dck[i] = -dck[i - 1];
            }
            for (i = 0; i < npow; i++)
            {
                for(j = 1; j < npow - i; j++)
                {
                    dck[npow + j] += dck[npow + j - 1];
                }
                k = 2 * i;
                for(j = 0; j < npow - i; j++)
                {
                    l = 2 * (i + j);
                    t = dck[j] * dck[npow + j];
                    aparam[k] += (t * (gparam[l] * pq[j] - gparam[l + 1] * pq[npow + j]));
                    aparam[k + 1] += (t * (gparam[l] * pq[npow + j] + gparam[l + 1] * pq[j]));
                }
            }
            fprintf(fpout, "key:\n");
            fprintf(fpout, " --0--:\n");
            fprintf(fpout, format1, aparam[0]);
            fprintf(fpout, format1, aparam[1]);
            for (i = 1; i < npow; i++)
            {
                fprintf(fpout, " --%d--:\n", i);
                j = 2 * i;
                fprintf(fpout, " %.12g\n", aparam[j]);
                fprintf(fpout, " %.12g\n", aparam[j + 1]);
            }
            fprintf(fpout, "\n");
            eparam[1] = ((eparam[0] > 0.0) && (npow > 1)) ? (eparam[1] / eparam[0]) : 0.0;
            eparam[0] = ycp[2] - eparam[1] * xcp[2];
            fprintf(fpout, "Elevation (H):\n");
            fprintf(fpout, "key:\n");
            fprintf(fpout, " --0--:\n");
            fprintf(fpout, format1, eparam[0]);
            if (npow > 1)
            {
                fprintf(fpout, " --1--:\n");
                fprintf(fpout, " %.12g\n", eparam[1]);
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
                    /* PQ-scheme by Alexander Starostin aka @stout */
                    pq[0] = 1.0;
                    pq[npow] = 0.0;
                    for (i = 1; i < npow; i++)
                    {
                        j = i + npow;
                        pq[i] = pq[i - 1] * x[0] - pq[j - 1] * x[1];
                        pq[j] = pq[i - 1] * x[1] + pq[j - 1] * x[0];
                    }
                    z[0] = 0.0;
                    z[1] = 0.0;
                    z[2] = eparam[0] + eparam[1] * x[2];
                    for (i = 0; i < npow; i++)
                    {
                        j = i + npow;
                        k = 2 * i;
                        z[0] += (pq[i] * aparam[k] - pq[j] * aparam[k + 1]);
                        z[1] += (pq[i] * aparam[k + 1] + pq[j] * aparam[k]);
                    }
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
                        fprintf(stderr, "Error in input, line skipped: \n%s\n", buf);
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
            fprintf(fpout, "The calculation is wrong! Reduce the conversion power!\n");
        }
        free(pq);
        free(gmat);
        free(gvec);
        free(gparam);
        free(aparam);
        free(dck);
    }
    else
    {
        fprintf(fpout, "No mating points found! Calculation is not possible!\n");
    }
    fclose(fpout);
    fclose(fpin);

    return 0;
}
