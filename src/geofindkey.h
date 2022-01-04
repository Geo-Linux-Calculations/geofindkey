/*
Name: geofinkey.h
Default params and functions.
(use Gauss normalize @zvezdochiot[https://geodesist.ru/members/zvezdochiot.47244/])
(use PQ-scheme by Alexander Starostin aka @stout[https://geodesist.ru/members/stout.228/])
(use Last published version of CCMATH by Daniel Atkinson in 2001 (version 2.2.1)[https://github.com/mnhrdt/ccmath].)
(use Gnumeric OLS spreadsheets [https://github.com/Geo-Linux-Calculations/gnumeric-ols])
Version: 3.2
Date: 2022-01-04
Author: Игорь Белов (https://gis-lab.info/forum/memberlist.php?mode=viewprofile&u=10457)
Author: zvezdochiot (https://github.com/zvezdochiot)
Author: Zoltan Siki (https://github.com/zsiki)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#ifndef __GEOFINDKEY_H
#define __GEOFINDKEY_H

#define PVERSION "3.2"

#define defDecimals 4
#define defREarth 6370009.0
#define defKAtm 0.0
#define defUnits "DEG"
#define defMode "CONST"
#define defMScale "NORM"
#define defEps 0.000001
#define defPOW -1
#define maxPOW 127

/*
Gauss normalize variable
mean = sum(w * x) / sum(w)
gnorm = 1.0 / sqrt(2.0 * (sum(w * x * x) / sum(w) - mean * mean))
*/
double gaussnorm(double x, double mean, double gnorm)
{
    x -= mean;
    x *= gnorm;
    return x;
}

/*
Invert matrix size n * n
(use Last published version of CCMATH by Daniel Atkinson in 2001 (version 2.2.1)[https://github.com/mnhrdt/ccmath].)
cond(a) = sqrt(sum(a .* a) * sum(ia .* ia))
*/
double minv(double *a, int n)
{
    int lc, *le;
    double s, t, tq = 0.0, zr = 1.0e-15, sumaa, conda;
    double *pa, *pd, *ps, *p, *q, *q0;
    int i, j, k, m;
    le = (int *)malloc(n * sizeof(int));
    q0 = (double *)malloc(n * sizeof(double));
    sumaa = 0.0;
    for(j = 0, pa = a; j < (n * n); ++j, ++pa) sumaa += (*pa * *pa);
    conda = sqrt(sumaa);
    for(j = 0, pa = pd = a; j < n; ++j, ++pa, pd += (n + 1))
    {
        if(j > 0)
        {
            for(i = 0, q = q0, p = pa; i < n; ++i, p += n) *q++ = *p;
            for(i = 1; i < n; i++)
            {
                lc = (i < j) ? i : j;
                for(k = 0, p = (pa + i * n - j), q = q0, t = 0.; k < lc; ++k) t += (*p++ * *q++);
                q0[i] -= t;
            }
            for(i = 0, q = q0, p = pa; i < n; ++i,p += n) *p = *q++;
        }
        s = fabs(*pd);
        lc = j;
        for(k = (j + 1), ps = pd; k < n; ++k)
        {
            if((t = fabs(*(ps += n)))>s)
            {
                s = t;
                lc = k;
            }
        }
        tq = (tq > s) ? tq : s;
        if(s < (zr * tq))
        {
            free(le-j);
            free(q0);
            return -1.0;
        }
        *le++ = lc;
        if(lc != j)
        {
            for(k = 0, p = (a + n * j), q = (a + n * lc); k < n; ++k)
            {
                t = *p;
                *p++ = *q;
                *q++ = t;
            }
        }
        for(k = (j + 1), ps = pd, t = (1.0 / *pd); k < n; ++k) *(ps += n) *= t;
        *pd = t;
    }
    for(j = 1, pd = ps = a; j < n; j++)
    {
        for(k = 0, pd += (n + 1), q = ++ps; k < j; ++k, q += n) *q *= *pd;
    }
    for(j = 1, pa = a; j < n; j++)
    {
        pa++;
        for(i = 0, q = q0, p = pa; i < j; ++i, p += n) *q++ = *p;
        for(k = 0; k < j; k++)
        {
            t = 0.0;
            for(i = k, p = (pa + k * n + k - j), q = (q0 + k); i < j; ++i) t -= (*p++ * *q++);
            q0[k] = t;
        }
        for(i = 0, q = q0, p = pa; i < j; i++, p += n) *p = *q++;
    }
    for(j = (n - 2), pd = pa = (a + n * n - 1); j >= 0; --j)
    {
        pa--;
        pd -= (n + 1);
        for(i = 0, m = (n - j - 1), q = q0, p = (pd + n); i < m; ++i, p += n) *q++ = *p;
        for(k = (n - 1), ps = pa; k > j; --k, ps -= n)
        {
            t = -(*ps);
            for(i = (j + 1), p = ps, q = q0; i < k; ++i) t -= (*++p * *q++);
            q0[--m] =t ;
        }
        for(i = 0, m = (n - j - 1), q = q0, p = (pd + n); i < m; ++i, p += n) *p = *q++;
    }
    for(k = 0, pa = a; k < (n - 1); ++k, ++pa)
    {
        for(i = 0, q = q0, p = pa; i < n; ++i, p += n) *q++ = *p;
        for(j = 0, ps = a; j < n; ++j, ps += n)
        {
            if(j > k)
            {
                t = 0.0;
                p = ps + j;
                i = j;
            }
            else
            {
                t = q0[j];
                p = ps + k + 1;
                i = k + 1;
            }
            for(; i < n;) t += (*p++ * q0[i++]);
            q0[j] = t;
        }
        for(i = 0, q = q0, p = pa; i < n; ++i, p += n) *p = *q++;
    }
    for(j = (n - 2), le--; j >= 0; --j)
    {
        for(k = 0, p = (a + j), q = (a + *(--le)); k < n; ++k, p += n, q += n)
        {
            t = *p;
            *p = *q;
            *q = t;
        }
    }
    free(le);
    free(q0);
    sumaa = 0.0;
    for(j = 0, pa = a; j < (n * n); ++j, ++pa) sumaa += (*pa * *pa);
    conda *= sqrt(sumaa);
    return conda;
}

#endif
