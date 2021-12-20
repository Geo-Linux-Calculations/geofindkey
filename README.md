![GitHub release (latest by date)](https://img.shields.io/github/v/release/Geo-Linux-Calculations/geofindkey)
![GitHub Release Date](https://img.shields.io/github/release-date/Geo-Linux-Calculations/geofindkey)
![GitHub repo size](https://img.shields.io/github/repo-size/Geo-Linux-Calculations/geofindkey)
![GitHub all releases](https://img.shields.io/github/downloads/Geo-Linux-Calculations/geofindkey/total)
![GitHub](https://img.shields.io/github/license/Geo-Linux-Calculations/geofindkey)

# GeoFindKey

Conformal transformation.

Conformal transformation on the plane is widely used in geodesy when creating local coordinate systems in small areas, limited by the size of the settlement.

Based of [Coordinates transformation orthogonal](./doc/CTO.md)

Theory and practice:
* [COORDINATE TRANSFORMATIONS FOR CADASTRAL SURVEYING](./doc/CTC.pdf)
* [Weighted Coordinate Transformations](./doc/WCT.pdf)
* [conformal transformations 1-4 power](./doc/conformal_trans_1-4power-ru.cbz)

## DOCUMENTATION

See doc/*

## BUILD

The procedure for compiling is:
```sh
make
```

---

## SAMPLE

### GeoFindKey:

Input Data doc/data.dat:
```
1 1334.71   285.94 66.29 83477.64 47377.60 216.28 1.0
2  563.67 -5197.34 60.21 82557.14 41916.51 210.21 1.0
3 4444.27  1153.79 67.76 86610.19 48160.39 217.77 1.0
4 -252.07  2881.90 65.41 81962.05 50016.34 215.42 1.0
5 1334.71   285.94 66.29
6  563.67 -5197.34 60.21
7 4444.27  1153.79 67.76
8 -252.07  2881.90 65.41
```

#### Mode Normal:
```sh
./geofindkey doc/data.dat report.dat
```

Result report.dat:
```
key:
(NORM)
--0-----
82135.4073
47128.1437
149.9631
--1-----
0.999787994227
-0.027289778074
1.000606333521
========
1.000160369835
-1.5635324426

var:
1 1334.7100 285.9400 66.2900 83477.6400 47377.6000 216.2800 1 -0.0024 -0.0008 +0.0133 -0.0002735462 -0.0000
2 563.6700 -5197.3400 60.2100 82557.1400 41916.5100 210.2100 1 -0.0165 +0.0132 -0.0004 0.0002137624 +0.0093
3 4444.2700 1153.7900 67.7600 86610.1900 48160.3900 217.7700 1 +0.0318 +0.0160 -0.0058 -0.0000341993 -0.0355
4 -252.0700 2881.9000 65.4100 81962.0500 50016.3400 215.4200 1 -0.0129 -0.0283 -0.0072 -0.0003963128 +0.0189
5 1334.7100 285.9400 66.2900 83477.6376 47377.5992 216.2933
6 563.6700 -5197.3400 60.2100 82557.1235 41916.5232 210.2096
7 4444.2700 1153.7900 67.7600 86610.2218 48160.4060 217.7642
8 -252.0700 2881.9000 65.4100 81962.0371 50016.3117 215.4128

diff:
0.0269 0.0248 0.0115 0.0003672639 0.0292
```

#### Mode Rescale:
```sh
./geofindkey -m EQUAL doc/data.dat report.dat
```

Result report.dat:
```
zvezdochiot@devuan-zvezdochiot:~/WORK/git/geo/geofindkey$ cat report.dat 
key:
(EQUAL)
--0-----
82135.6504
47128.1020
150.0025
--1-----
0.999627684101
-0.027285402318
1.000000000000
========
1.000160369835
-1.5635324426

var:
1 1334.7100 285.9400 66.2900 83477.6400 47377.6000 216.2800 1 +0.0255 -0.0826 +0.0125 -0.0002735462 +0.0864
2 563.6700 -5197.3400 60.2100 82557.1400 41916.5100 210.2100 1 +0.1591 +0.8071 +0.0025 0.0002137624 +0.8224
3 4444.2700 1153.7900 67.7600 86610.1900 48160.3900 217.7700 1 -0.4426 -0.1913 -0.0075 -0.0000341993 +0.4822
4 -252.0700 2881.9000 65.4100 81962.0500 50016.3400 215.4200 1 +0.2581 -0.5332 -0.0075 -0.0003963128 +0.5918
5 1334.7100 285.9400 66.2900 83477.6655 47377.5174 216.2925
6 563.6700 -5197.3400 60.2100 82557.2991 41917.3171 210.2125
7 4444.2700 1153.7900 67.7600 86609.7474 48160.1987 217.7625
8 -252.0700 2881.9000 65.4100 81962.3081 50015.8068 215.4125

diff:
0.3798 0.6997 0.0117 0.0003672639 0.7958
```

### GeoFindKey 2 power:
```sh
./geofindkey2p doc/data.dat report.dat
```

Result report.dat:
```
key:
--0-----
82135.4060
47128.1486
150.3057
--1-----
0.999791518237
-0.027293637599
0.989847192109
--2-----
-0.000000001537
0.000000000324
0.000084448305
========
1.000163997848
-1.5637479503

var:
1 1334.7100 285.9400 66.2900 83477.6400 47377.6000 216.2800 1 -0.0007 -0.0007 +0.0138
2 563.6700 -5197.3400 60.2100 82557.1400 41916.5100 210.2100 1 +0.0072 -0.0021 +0.0006
3 4444.2700 1153.7900 67.7600 86610.1900 48160.3900 217.7700 1 +0.0190 -0.0020 -0.0045
4 -252.0700 2881.9000 65.4100 81962.0500 50016.3400 215.4200 1 +0.0093 -0.0127 -0.0071
5 1334.7100 285.9400 66.2900 83477.6393 47377.5993 216.2938
6 563.6700 -5197.3400 60.2100 82557.1472 41916.5079 210.2106
7 4444.2700 1153.7900 67.7600 86610.2090 48160.3880 217.7655
8 -252.0700 2881.9000 65.4100 81962.0593 50016.3273 215.4129

diff:
0.0158 0.0092 0.0114
```

### Helmert transform:
```sh
./geohelmert3d doc/data.dat report.dat
```

Result report.dat:
```
Mean: 4
M 1522.6450 -218.9275 64.9175 83651.7550 46867.7100 214.9200
NORM = 0.000285193
cond(G) = 7.24047
key:
 82135.4074
 47128.1438
 150.0150
 0.999787994766
 1.17227e-06
 -9.68991e-07
 -0.0272898

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
```

### S-Z-B to Y-X-H convert:

Input Data doc/szb.dat:
```
OKD-4     8.605  74.08666667   234.38916667  7471.2970  14588.7117  98.7445
OKD-5     8.869  81.18888889   254.73888889  7474.2548  14589.4514  97.7433
OKD-K3-1  3.670  82.43944444   339.05361111  7477.0949  14580.7517  96.8713
OKD-K3-4  3.690  70.66833333   161.16        7469.9723  14580.8231  97.6075
OKD-K5P   3.938  71.95527778   137.52222222  7469.9811  14579.3211  97.6057
OKD-K7L   4.685  83.96444444   17.82444444   7477.1099  14577.8330  96.8789
OKD-K7L   4.684  276.03361111  197.82722222  7477.1099  14577.8330  96.8789
OKD-K5P   3.939  288.04361111  317.52472222  7469.9811  14579.3211  97.6057
OKD-K3-4  3.691  289.32972222  341.16111111  7469.9723  14580.8231  97.6075
OKD-K3-1  3.671  277.55583333  159.05805556  7477.0949  14580.7517  96.8713
OKD-5     8.869  278.80944444  74.74055556   7474.2548  14589.4514  97.7433
OKD-4     8.604  285.91444444  54.38972222   7471.2970  14588.7117  98.7445
OKD-11    3.889  71.6025       313.60777778
OKD-12    3.889  288.39138889  133.60805556
```

Exec convert:
```sh
./geoszbtoyxh doc/szb.dat yxh.dat
```

Result yxh.dat:
```
OKD-4 -6.7277 -4.8185 2.3593 7471.2970 14588.7117 98.7445 1
OKD-5 -8.4553 -2.3069 1.3585 7474.2548 14589.4514 97.7433 1
OKD-K3-1 -1.3006 3.3977 0.4829 7477.0949 14580.7517 96.8713 1
OKD-K3-4 1.1244 -3.2954 1.2215 7469.9723 14580.8231 97.6075 1
OKD-K5P 2.5285 -2.7616 1.2198 7469.9811 14579.3211 97.6057 1
OKD-K7L 1.4261 4.4354 0.4926 7477.1099 14577.8330 96.8789 1
OKD-K7L 1.4261 4.4344 0.4923 7477.1099 14577.8330 96.8789 1
OKD-K5P 2.5291 -2.7624 1.2201 7469.9811 14579.3211 97.6057 1
OKD-K3-4 1.1247 -3.2964 1.2217 7469.9723 14580.8231 97.6075 1
OKD-K3-1 -1.3007 3.3987 0.4827 7477.0949 14580.7517 96.8713 1
OKD-5 -8.4554 -2.3067 1.3583 7474.2548 14589.4514 97.7433 1
OKD-4 -6.7269 -4.8178 2.3592 7471.2970 14588.7117 98.7445 1
OKD-11 -2.6720 2.5452 1.2274
OKD-12 -2.6721 2.5453 1.2270
```

### SIter (estimation of unknown distances):

Input Data doc/szbunknow.dat:
```
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
```

Exec finding unknown distances:
```sh
./geositer500 doc/szbunknow.dat szb.dat
```

Result sbz.dat:
```
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
```

### Deformation:

Input Data doc/gps.dat:
```
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
```

Exec finding unknown distances:
```sh
./geodeform500 doc/gps.dat gpsout.dat
```

Result gpsout.dat:
```
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
```

---

https://github.com/Geo-Linux-Calculations/geofindkey
