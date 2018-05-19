/*
Name: geofindkey.c
OldName: findkey.c
Date: 2018-05-19
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
 
int main(int argc, char *argv[])
{
  char buf[1024], name[32];
  double x[2], y[2], wgt;
  double xc[2], yc[2];
  double dx[2], dy[2], dz[2];
  double a[2][2], scale, rotation;
  double s[5];
  int i;
  FILE *fp0, *fp1;
 
  if (argc < 3) {
    printf("usage: geofindkey input-file report-file\n");
    exit(EXIT_FAILURE);
  }
 
  if ((fp0 = fopen(argv[1], "r")) == NULL) {
    printf("can't open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
 
  /* подсчитать сумму координат */
  for (i = 0; i < 5; i++)
    s[i] = 0.;
  while (fgets(buf, 1024, fp0) != NULL) {
    sscanf(buf, "%s %lf %lf %lf %lf %lf",
	   name, &x[0], &x[1], &y[0], &y[1], &wgt);
    s[0] += x[0] * wgt;
    s[1] += x[1] * wgt;
    s[2] += y[0] * wgt;
    s[3] += y[1] * wgt;
    s[4] += wgt;
  }
  rewind(fp0);
 
  /* найти центр масс */
  for (i = 0; i < 2; i++) {
    xc[i] = s[i] / s[4];
    yc[i] = s[2 + i] / s[4];
  }
 
  /* подсчитать сумму произведений */
  for (i = 0; i < 5; i++)
    s[i] = 0.;
  while (fgets(buf, 1024, fp0) != NULL) {
    sscanf(buf, "%s %lf %lf %lf %lf %lf",
	   name, &x[0], &x[1], &y[0], &y[1], &wgt);
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
  rewind(fp0);
 
  /* найти первичные параметры */
  a[1][0] = (s[0] + s[1]) / s[4];
  a[1][1] = (s[2] - s[3]) / s[4];
  a[0][0] = yc[0] - a[1][0] * xc[0] + a[1][1] * xc[1];
  a[0][1] = yc[1] - a[1][1] * xc[0] - a[1][0] * xc[1];
 
  /* найти вторичные параметры */
  scale = hypot(a[1][0], a[1][1]);
  rotation = atan2(a[1][1], a[1][0]);
 
  /* вывести параметры в файл ключа */
  if ((fp1 = fopen(argv[2], "w")) == NULL) {
    printf("can't create %s\n", argv[2]);
    exit(EXIT_FAILURE);
  }
  fprintf(fp1, "key:\n");
  fprintf(fp1, "%.3f\n", a[0][0]);
  fprintf(fp1, "%.3f\n", a[0][1]);
  fprintf(fp1, "%.12f\n", a[1][0]);
  fprintf(fp1, "%.12f\n", a[1][1]);
  fprintf(fp1, "%.12f\n", scale);
  fprintf(fp1, "%+.10f\n", rotation * 180. / M_PI);
  fprintf(fp1, "\n");
 
  /* вывести данные вместе с невязками */
  fprintf(fp1, "var:\n");
  while (fgets(buf, 1024, fp0) != NULL) {
    sscanf(buf, "%s %lf %lf %lf %lf %lf",
	   name, &x[0], &x[1], &y[0], &y[1], &wgt);
    /* "наблюдённые" dx[], dy[] */
    dx[0] = x[0] - xc[0];
    dx[1] = x[1] - xc[1];
    dy[0] = y[0] - yc[0];
    dy[1] = y[1] - yc[1];
    /* "вычисленные" dy[] */
    dz[0] = a[1][0] * dx[0] - a[1][1] * dx[1];
    dz[1] = a[1][1] * dx[0] + a[1][0] * dx[1];
    fprintf(fp1, "%s %.3f %.3f %.3f %.3f %g %.3f %.3f\n",
	    name, x[0], x[1], y[0], y[1], wgt, dy[0] - dz[0], dy[1] - dz[1]);
  }
  fclose(fp1);
 
  fclose(fp0);
 
  return 0;
}
