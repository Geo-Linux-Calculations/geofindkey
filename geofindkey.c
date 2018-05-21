/*
Name: geofindkey.c
OldName: findkey.c
Date: 2018-05-20
Author: Игорь Белов (https://gis-lab.info/forum/memberlist.php?mode=viewprofile&u=10457)
Author: zvezdochiot (https://github.com/zvezdochiot)
*
build:
$ gcc -o geofindkey geofindkey.c -lm
sample:
$ ./geofindkey doc/data.dat report.dat
*
file:
input file doc/data.dat:
*
1 1334.71   285.94 83477.64 87377.60 1.0
2  563.67 -5197.34 82557.14 81916.51 1.0
3 4444.27  1153.79 86610.19 88160.39 1.0
4 -252.07  2881.90 81962.05 90016.34 1.0
*
output file report.dat:
*
key:
82135.407
87128.144
0.999787994227
-0.027289778074
1.000160369835
-1.5635324426

var:
1 1334.710 285.940 83477.640 87377.600 1 0.002 0.001
2 563.670 -5197.340 82557.140 81916.510 1 0.016 -0.013
3 4444.270 1153.790 86610.190 88160.390 1 -0.032 -0.016
4 -252.070 2881.900 81962.050 90016.340 1 0.013 0.028
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define PNAME "GeoFindKey"
#define PVERSION "1.3"

void geofindkeytitle()
{
    printf("%s %s\n", PNAME, PVERSION);
}

void geofindkeyusage()
{
    printf("usage: geofindkey [option] input-file report-file\n");
    printf("options:\n");
    printf("          -r      rescale mode (bool, optional, default = false)\n");
    printf("          -s      station mode (bool, optional, default = false)\n");
    printf("          -h      this help\n");
    printf("\n");
    printf("input-file(sample):\n");
    printf(" 1 1334.71   285.94 83477.64 87377.60 1.0\n");
    printf(" 2  563.67 -5197.34 82557.14 81916.51 1.0\n");
    printf(" 3 4444.27  1153.79 86610.19 88160.39 1.0\n");
    printf(" 4 -252.07  2881.90 81962.05 90016.34 1.0\n");
    printf(" 5 1334.71   285.94\n");
    printf(" 6  563.67 -5197.34\n");
    printf(" 7 4444.27  1153.79\n");
    printf(" 8 -252.07  2881.90\n");
    printf("\n");
    printf("report-file(sample):\n");
    printf(" key:\n");
    printf(" 82135.4073\n");
    printf(" 47128.1437\n");
    printf(" 0.999787994227\n");
    printf(" -0.027289778074\n");
    printf(" 1.000160369835\n");
    printf(" -1.5635324426\n");
    printf(" \n");
    printf(" var:\n");
    printf(" (Mode Normal)\n");
    printf(" 1 1334.7100 285.9400 83477.6400 47377.6000 1 +0.0024 +0.0008 -0.0002735462 -0.0000\n");
    printf(" 2 563.6700 -5197.3400 82557.1400 41916.5100 1 +0.0165 -0.0132 +0.0002137624 +0.0093\n");
    printf(" 3 4444.2700 1153.7900 86610.1900 48160.3900 1 -0.0318 -0.0160 -0.0000341993 -0.0355\n");
    printf(" 4 -252.0700 2881.9000 81962.0500 50016.3400 1 +0.0129 +0.0283 -0.0003963128 +0.0189\n");
    printf(" 5 1334.7100 285.9400 83477.6376 47377.5992\n");
    printf(" 6 563.6700 -5197.3400 82557.1235 41916.5232\n");
    printf(" 7 4444.2700 1153.7900 86610.2218 48160.4060\n");
    printf(" 8 -252.0700 2881.9000 81962.0371 50016.3117\n");
    printf(" \n");
    printf(" diff:\n");
    printf(" 0.0269 0.0248 0.0003672639 0.0292\n");
}

int main(int argc, char *argv[])
{
    char buf[1024], name[32];
    double x[2], y[2], wgt;
    double xc[2], yc[2];
    double dx[2], dy[2], dz[2], vdz[2];
    double a[2][2], scale, rotation, ay, az, da, say, saz, ds;
    double s[6];
    int i, np;
    FILE *fp0, *fp1;

    int opt;
    int fstation = 0;
    int frescale = 0;
    int fhelp = 0;
    while ((opt = getopt(argc, argv, ":rsh")) != -1)
    {
        switch(opt)
        {
            case 'r':
                frescale = 1;
                break;
            case 's':
                fstation = 1;
                break;
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

    geofindkeytitle();

    if ((optind + 2 > argc) || (fhelp > 0))
    {
        geofindkeyusage();
        exit(0);
    }

    if ((fp0 = fopen(argv[optind], "r")) == NULL)
    {
        printf("can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* подсчитать сумму координат */
    for (i = 0; i < 6; i++) {s[i] = 0.;}
    while (fgets(buf, 1024, fp0) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf", name, &x[0], &x[1], &y[0], &y[1], &wgt);
        if (np >= 6)
        {
            s[0] += x[0] * wgt;
            s[1] += x[1] * wgt;
            s[2] += y[0] * wgt;
            s[3] += y[1] * wgt;
            s[4] += wgt;
        }
    }
    rewind(fp0);

    /* найти центр масс */
    for (i = 0; i < 2; i++)
    {
        xc[i] = s[i];
        yc[i] = s[2 + i];
        if (s[4] != 0)
        {
            xc[i] /= s[4];
            yc[i] /= s[4];
        }
    }

    /* подсчитать сумму произведений */
    for (i = 0; i < 6; i++) {s[i] = 0.;}
    while (fgets(buf, 1024, fp0) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf", name, &x[0], &x[1], &y[0], &y[1], &wgt);
        if (np >= 6)
        {
            /* вычислить разности */
            dx[0] = x[0] - xc[0];
            dx[1] = x[1] - xc[1];
            dy[0] = y[0] - yc[0];
            dy[1] = y[1] - yc[1];
            /* суммировать */
            s[0] += dx[0] * dy[0] * wgt;
            s[1] += dx[1] * dy[1] * wgt;
            s[2] += dx[0] * dy[1] * wgt;
            s[3] += dx[1] * dy[0] * wgt;
            s[4] += (dx[0] * dx[0] + dx[1] * dx[1]) * wgt;
        }
    }
    rewind(fp0);

    /* найти первичные параметры */
    a[1][0] = (s[0] + s[1]);
    a[1][1] = (s[2] - s[3]);
    if (s[4] != 0)
    {
        a[1][0] /= s[4];
        a[1][1] /= s[4];
    }
    a[0][0] = yc[0] - a[1][0] * xc[0] + a[1][1] * xc[1];
    a[0][1] = yc[1] - a[1][1] * xc[0] - a[1][0] * xc[1];

    /* найти вторичные параметры */
    scale = hypot(a[1][0], a[1][1]);
    rotation = atan2(a[1][1], a[1][0]);

    /* вывести параметры в файл ключа */
    if ((fp1 = fopen(argv[optind + 1], "w")) == NULL)
    {
        printf("can't create %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    fprintf(fp1, "key:\n");
    fprintf(fp1, "%.4f\n", a[0][0]);
    fprintf(fp1, "%.4f\n", a[0][1]);
    fprintf(fp1, "%.12f\n", a[1][0]);
    fprintf(fp1, "%.12f\n", a[1][1]);
    fprintf(fp1, "%.12f\n", scale);
    fprintf(fp1, "%+.10f\n", rotation * 180. / M_PI);
    fprintf(fp1, "\n");

    if (fstation > 0)
    {
        xc[0] = 0;
        xc[1] = 0;
        yc[0] = a[0][0];
        yc[1] = a[0][1];
    }

    if (frescale > 0 && scale != 0)
    {
        a[1][0] /= scale;
        a[1][1] /= scale;
    }

    /* вывести данные вместе с невязками */
    fprintf(fp1, "var:\n");
    if (frescale > 0)
    {
        if (fstation > 0)
        {
            fprintf(fp1, "(Mode Station Rescale)\n");
        } else {
            fprintf(fp1, "(Mode Rescale)\n");
        }
    } else {
        if (fstation > 0)
        {
            fprintf(fp1, "(Mode Station)\n");
        } else {
            fprintf(fp1, "(Mode Normal)\n");
        }
    }
    for (i = 0; i < 6; i++) {s[i] = 0.;}
    while (fgets(buf, 1024, fp0) != NULL)
    {
        np = sscanf(buf, "%s %lf %lf %lf %lf %lf", name, &x[0], &x[1], &y[0], &y[1], &wgt);
        /* "наблюдённые" dx[], dy[] */
        dx[0] = x[0] - xc[0];
        dx[1] = x[1] - xc[1];
        /* "вычисленные" dy[] */
        dz[0] = a[1][0] * dx[0] - a[1][1] * dx[1];
        dz[1] = a[1][1] * dx[0] + a[1][0] * dx[1];
        az = atan2(dz[1], dz[0]);
        saz = hypot(dz[0], dz[1]);
        if (np >= 6)
        {
            dy[0] = y[0] - yc[0];
            dy[1] = y[1] - yc[1];
            vdz[0] = dy[0] - dz[0];
            vdz[1] = dy[1] - dz[1];
            s[0] += vdz[0] * vdz[0] * wgt;
            s[1] += vdz[1] * vdz[1] * wgt;
            say = hypot(dy[0], dy[1]);
            ds = say - saz;
            s[2] += ds * ds * wgt;
            s[4] += wgt;
            ay = atan2(dy[1], dy[0]);
            da = ay - az;
            da *= 180. / M_PI;
            s[3] += da * da * say * wgt;
            s[5] += say * wgt;
            fprintf(fp1, "%s %.4f %.4f %.4f %.4f %g %+.4f %+.4f %+.10f %+.4f\n", name, x[0], x[1], y[0], y[1], wgt, vdz[0], vdz[1], da, ds);
        } else {
            dy[0] = dz[0];
            dy[1] = dz[1];
            y[0] = yc[0] + dy[0];
            y[1] = yc[1] + dy[1];
            fprintf(fp1, "%s %.4f %.4f %.4f %.4f\n", name, x[0], x[1], y[0], y[1]);
        }
    }
    if (s[4] != 0)
    {
		for (i = 0; i < 3; i++)
		{
			s[i] /= s[4];
		}
    }
    if (s[5] != 0)
    {
        s[3] /= s[5];
    }
	for (i = 0; i < 4; i++)
	{
		s[i] *= 2;
		s[i] = sqrt(s[i]);
	}
    fprintf(fp1, "\n");
    fprintf(fp1, "diff:\n");
    fprintf(fp1, "%.4f %.4f %.10f %.4f \n", s[0], s[1], s[3], s[2]);
    fclose(fp1);
    fclose(fp0);

    return 0;
}
