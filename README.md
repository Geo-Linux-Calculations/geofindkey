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

    1 1334.71   285.94 83477.64 47377.60 1.0
    2  563.67 -5197.34 82557.14 41916.51 1.0
    3 4444.27  1153.79 86610.19 48160.39 1.0
    4 -252.07  2881.90 81962.05 50016.34 1.0
    5 1334.71   285.94
    6  563.67 -5197.34
    7 4444.27  1153.79
    8 -252.07  2881.90

    Result report.dat:

    key:
    82135.4073
    47128.1437
    0.999787994227
    -0.027289778074
    1.000160369835
    -1.5635324426
    
    var:
    1 1334.7100 285.9400 83477.6400 47377.6000 1 0.0024 0.0008
    2 563.6700 -5197.3400 82557.1400 41916.5100 1 0.0165 -0.0132
    3 4444.2700 1153.7900 86610.1900 48160.3900 1 -0.0318 -0.0160
    4 -252.0700 2881.9000 81962.0500 50016.3400 1 0.0129 0.0283
    5 1334.7100 285.9400 83477.6376 47377.5992
    6 563.6700 -5197.3400 82557.1235 41916.5232
    7 4444.2700 1153.7900 86610.2218 48160.4060
    8 -252.0700 2881.9000 81962.0371 50016.3117

https://github.com/zvezdochiot/geofindkey
