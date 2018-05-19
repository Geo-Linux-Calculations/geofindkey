# GeoFindKey
Conformal transformation

Conformal transformation on the plane is widely used in geodesy when creating local coordinate systems in small areas, limited by the size of the settlement.

## DOCUMENTATION

See doc/*

## BUILD

The procedure for compiling is:

    make

## SAMPLE

    ./geofindkey doc/data.dat report.dat

    doc/data.dat:

    1 1334.71   285.94 83477.64 87377.60 1.0
    2  563.67 -5197.34 82557.14 81916.51 1.0
    3 4444.27  1153.79 86610.19 88160.39 1.0
    4 -252.07  2881.90 81962.05 90016.34 1.0

    Result report.dat:

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

https://github.com/zvezdochiot/geofindkey
