#ifndef _PREDICT_DEFS_H_
#define _PREDICT_DEFS_H_

/* Constants used by SGP4/SDP4 code */
static const double km2mi	=	0.621371;		/* km to miles */
static const double deg2rad = 1.745329251994330E-2;	/* Degrees to radians */
static const double pi = 3.14159265358979323846;	/* Pi */
static const double pio2 = 1.57079632679489656;	/* Pi/2 */
static const double twopi = 6.28318530717958623;     /* 2*Pi  */
static const double x3pio2 = 4.71238898038468967;	/* 3*Pi/2 */
static const double e6a = 1.0E-6;
static const double tothrd = 6.6666666666666666E-1;	/* 2/3 */
static const double xj2 = 1.0826158E-3;	/* J2 Harmonic (WGS '72) */
static const double xj3 = -2.53881E-6;		/* J3 Harmonic (WGS '72) */
static const double xj4 = -1.65597E-6;		/* J4 Harmonic (WGS '72) */
static const double xke = 7.43669161E-2;
static const double xkmper = 6.378137E3;		/* WGS 84 Earth radius km */
static const double xmnpda = 1.44E3;			/* Minutes per day */
static const double ae = 1.0;
static const double ck2 = 5.413079E-4;
static const double ck4 = 6.209887E-7;
static const double f = 3.35281066474748E-3;	/* Flattening factor */
static const double ge = 3.986008E5; 	/* Earth gravitational constant (WGS '72) */
static const double s = 1.012229;
static const double qoms2t = 1.880279E-09;
static const double secday = 8.6400E4;	/* Seconds per day */
static const double omega_E = 1.00273790934;	/* Earth rotations/siderial day */
static const double omega_ER = 6.3003879;	/* Earth rotations, rads/siderial day */
static const double zns = 1.19459E-5;
static const double c1ss = 2.9864797E-6;
static const double zes = 1.675E-2;
static const double znl = 1.5835218E-4;
static const double c1l = 4.7968065E-7;
static const double zel = 5.490E-2;
static const double zcosis = 9.1744867E-1;
static const double zsinis = 3.9785416E-1;
static const double zsings = -9.8088458E-1;
static const double zcosgs = 1.945905E-1;
static const double zcoshs = 1;
static const double zsinhs = 0;
static const double q22 = 1.7891679E-6;
static const double q31 = 2.1460748E-6;
static const double q33 = 2.2123015E-7;
static const double g22 = 5.7686396;
static const double g32 = 9.5240898E-1;
static const double g44 = 1.8014998;
static const double g52 = 1.0508330;
static const double g54 = 4.4108898;
static const double root22 = 1.7891679E-6;
static const double root32 = 3.7393792E-7;
static const double root44 = 7.3636953E-9;
static const double root52 = 1.1428639E-7;
static const double root54 = 2.1765803E-9;
static const double thdt = 4.3752691E-3;
static const double rho = 1.5696615E-1;
static const double mfactor = 7.292115E-5;
static const double sr = 6.96000E5; /* Solar radius - km (IAU 76) */
static const double AU = 1.49597870691E8; /* Astronomical unit - km (IAU 76) */

/* doppler calculation */
static const double SPEED_OF_LIGHT = 299792458.0;


#endif
