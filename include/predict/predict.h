#ifndef _PREDICT_H_
#define _PREDICT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <stdbool.h>

/**
 * The representation of time used by libpredict: The number of days since 31Dec79 00:00:00 UTC. 
 **/
typedef double predict_julian_date_t;

/**
 * Convert time_t in UTC to Julian date in UTC.
 *
 * \param time Time in UTC
 * \return Julian day in UTC
 **/
predict_julian_date_t predict_to_julian(time_t time);

/**
 * Convert Julian date in UTC back to a time_t in UTC. 
 *
 * \param date Julian date in UTC
 * \return Time in UTC
 **/
time_t predict_from_julian(predict_julian_date_t date);

/**
 * Container for processed TLE data from TLE strings.
 **/
typedef struct {
	double epoch;
	double xndt2o;
	double xndd6o;
	double bstar;
	double xincl;
	double xnodeo;
	double eo;
	double omegao;
	double xmo;
	double xno;
 	int catnr;
	int elset;
	int revnum;
} predict_tle_t; 

/**
 * Simplified perturbation models used in modeling the satellite orbits. 
 **/
enum predict_ephemeris {
  EPHEMERIS_SGP4 = 0,
  EPHEMERIS_SDP4 = 1,
  EPHEMERIS_SGP8 = 2,
  EPHEMERIS_SDP8 = 3
};

/**
 * Satellite orbit definitions, according to defined NORAD TLE. 
 **/
typedef struct {
	///Name of satellite
	char name[128];

	///Timestamp for last call to orbit_predict
	predict_julian_date_t time;
	///ECI position in km
	double position[3];
	///ECI velocity in km/s
	double velocity[3];

	///Latitude in radians, northing/easting
	double latitude;
	///Longitude in radians, northing/easting
	double longitude;
	///Altitude in meters
	double altitude;
	///Whether satellite is eclipsed by the earth
	int eclipsed;
	///Eclipse depth
	double eclipse_depth;
	///Which perturbation model to use
	enum predict_ephemeris ephemeris;
	///Original TLE line number one:
	char line1[70];
	///Original TLE line number two:
	char line2[70];
	///Original tle_t used to hold processed tle parameters used in calculations.
	predict_tle_t tle;

	///Satellite number (line 1, field 2)
	long catnum;
	///Element number (line 1, field 13)
	long setnum;
	///International designator (line 1, fields 4, 5, 6)
	char designator[10];
	///Epoch year (last two digits) (line 1, field 7)
	int year;
	///Epoch day (day of year and fractional portion of day, line 1, field 8)
	double refepoch;
	///Inclination (line 2, field 3)
	double incl;
	///Right Ascension of the Ascending Node [Degrees] (line 2, field 4)
	double raan;
	///Eccentricity (decimal point assumed) (line 2, field 5)
	double eccn;
	///Argument of Perigee [Degrees] (line 2, field 6)
	double argper;
	///Mean Anomaly [Degrees] (line 2, field 7)
	double meanan;
	///Mean Motion [Revs per day] (line 2, field 8)
	double meanmo;
	///First Time Derivative of the Mean Motion divided by two (line 1, field 9)
	double drag;
	///Second Time Derivative of Mean Motion divided by six (decimal point assumed, line 1, field 10)
	double nddot6;
	///BSTAR drag term (decimal point assumed, line 1, field 11)
	double bstar;
	///Orbital number (line 2, field 9)
	long orbitnum;

	///Ephemeris data structure pointer
	void *ephemeris_data;
} predict_orbit_t;


/**
 * Create orbit structure. Allocate memory and prepare internal data.
 * \param tle NORAD two-line element set as string array
 * \return Allocated orbit structure
 * \copyright GPLv2+
 **/
predict_orbit_t *predict_create_orbit(const char *tle[]);

/**
 * Free memory allocated in orbit structure. 
 * \param orbit Orbit to free
 **/
void predict_destroy_orbit(predict_orbit_t *orbit);

/**
 * Main prediction function. Predict satellite orbit at given time. 
 * \param x Satellite orbit
 * \param time Julian day in UTC
 * \return 0 if everything went fine
 * \copyright GPLv2+
 **/
int predict_orbit(predict_orbit_t *x, predict_julian_date_t time);

/**
 * Find whether orbit is geostationary. 
 *
 * \param x Satellite orbit
 * \return true if orbit is geostationary, otherwise false
 * \copyright GPLv2+
 **/
bool predict_is_geostationary(const predict_orbit_t *x);

/** 
 * Get apogee of satellite orbit. 
 *
 * \param x Satellite orbit
 * \return Apogee of orbit
 * \copyright GPLv2+
 **/
double predict_apogee(const predict_orbit_t *x);

/**
 * Get perigee of satellite orbit. 
 *
 * \param x Satellite orbit
 * \return Perigee of orbit
 * \copyright GPLv2+
 **/
double predict_perigee(const predict_orbit_t *x);

/**
 * Find whether an AOS can ever happen on the given latitude. 
 *
 * \param x Satellite orbit
 * \param latitude Latitude of ground station
 * \return true if AOS can happen, otherwise false
 * \copyright GPLv2+
 **/
bool predict_aos_happens(const predict_orbit_t *x, double latitude);

/** 
 * Find whether an orbit has decayed.
 *
 * \param x Current state of orbit
 * \return true if orbit has decayed, otherwise false
 * \copyright GPLv2+
 **/
bool predict_decayed(const predict_orbit_t *x);

/** 
 * Find whether a satellite is currently eclipsed.
 *
 * \param x Current state of orbit
 * \return true if orbit is eclipsed, otherwise false
 **/
bool predict_is_eclipsed(const predict_orbit_t *x);

/** 
 * Return the eclipse depth
 *
 * \param x Current state of orbit
 * \return Eclipse depth (rad)
 **/
double predict_eclipse_depth(const predict_orbit_t *x);

/**
 * Observation point/ground station (QTH).
 **/
typedef struct {
	///Observatory name
	char name[128];
	///Latitude (WGS84, radians)
	double latitude;
	///Longitude (WGS84, radians)
	double longitude;
	///Altitude (WGS84, meters)
	double altitude;
} predict_observer_t;

/**
 * Data relevant for a relative observation of an orbit or similar with respect to an observation point.
 **/
struct predict_observation {
	///UTC time                
	predict_julian_date_t time;                       
	///Azimuth angle (rad)      
	double azimuth;
	///Azimuth angle rate (rad/s)
	double azimuth_rate;
	///Elevation angle (rad)                           
	double elevation;
	///Elevation angle rate (rad/s)
	double elevation_rate;
	///Range (km) 
	double range;                        
	///Range vector                    
	double range_x, range_y, range_z; 
	///Range velocity (km/s) 
	double range_rate;      
};

/**
 * Create observation point (QTH).
 *
 * \param name Name of observation point
 * \param lat Latitude in radians (easting/northing)
 * \param lon Longitude in radians (easting/northing)
 * \param alt Altitude in meters
 * \return Allocated observation point
 **/
predict_observer_t *predict_create_observer(const char *name, double lat, double lon, double alt);

/** 
 * Free observer.
 *
 * \param obs Observer to be freed.
 **/
void predict_destroy_observer(predict_observer_t *obs);

/** 
 * Find relative position of satellite with respect to an observer. Calculates range, azimuth, elevation and relative velocity.
 *
 * \param observer Point of observation
 * \param orbit Satellite orbit
 * \param obs Return of object for position of the satellite relative to the observer.
 * \copyright GPLv2+
 **/
void predict_observe_orbit(const predict_observer_t *observer, const predict_orbit_t *orbit, struct predict_observation *obs);

/**
 * Estimate relative position of the moon.
 *
 * \param observer Point of observation
 * \param time Time of observation
 * \param obs Return object for position of the moon relative to the observer
 * \copyright GPLv2+
 **/
void predict_observe_moon(const predict_observer_t *observer, predict_julian_date_t time, struct predict_observation *obs);

/** 
 * Estimate relative position of the sun.
 *
 * \param observer Point of observation
 * \param time Time of observation
 * \param obs Return object for position of the sun relative to the observer
 * \copyright GPLv2+
 **/
void predict_observe_sun(const predict_observer_t *observer, predict_julian_date_t time, struct predict_observation *obs);

/** 
 * Find next acquisition of signal (AOS) of satellite (when the satellite rises above the horizon). Ignores previous AOS of current pass if the satellite is in range at the start time. 
 *
 * \param observer Point of observation
 * \param orbit Satellite orbit
 * \param start_time Start time for AOS search
 * \return Time of AOS
 * \copyright GPLv2+
 **/
predict_julian_date_t predict_next_aos(const predict_observer_t *observer, predict_orbit_t *orbit, predict_julian_date_t start_time);

/** 
 * Find next loss of signal (LOS) of satellite (when the satellite goes below the horizon). Finds LOS of the current pass if the satellite currently is in range, finds LOS of next pass if not.
 *
 * \param observer Point of observation
 * \param orbit Satellite orbit
 * \param start_time Start time for LOS search
 * \return Time of LOS
 * \copyright GPLv2+
 **/
predict_julian_date_t predict_next_los(const predict_observer_t *observer, predict_orbit_t *orbit, predict_julian_date_t start_time);

/**
 * Calculate doppler shift of a given downlink frequency with respect to the observer. 
 *
 * \param observer Point of observation
 * \param orbit Current state of satellite orbit
 * \param downlink_frequency Downlink frequency of the satellite
 * \return The frequency difference from the original frequency
 * \copyright GPLv2+
 **/
double predict_doppler_shift(const predict_observer_t *observer, const predict_orbit_t *orbit, double downlink_frequency);

/*!
 * \brief Calculate refraction angle.
 *
 * This function assumes atmospheric pressure of 101.0kPa and temperature 10deg celsius.
 *
 * \param el True elevation angle (rad).
 *
 * \return Refraction angle (rad).
 */
double predict_refraction(double el);

/*!
 * \brief Calculate refraction angle.
 *
 * Corrects for different atmospheric pressure and temperature.
 *
 * \param el True elevation angle in rads.
 * \param pressure Atmospheric pressure in kPa.
 * \param temp Temperature in deg celsius.
 *
 * \return Refraction angle (rad).
 */
double predict_refraction_ext(double el, double pressure, double temp);

/*!
 * \brief Calculate refraction angle from apparent elevation.
 *
 * This function assumes atmospheric pressure of 101.0kPa and temperature 10deg celsius.
 *
 * \param apparent_el Apparent elevation angle (rad).
 *
 * \return Refraction angle (rad).
 */
double predict_refraction_from_apparent(double apparent_el);

/*!
 * \brief Calculate refraction angle from apparent elevation.
 *
 * Corrects for different atmospheric pressure and temperature.
 *
 * \param apparent_el Apparent elevation angle (rad).
 * \param pressure Atmospheric pressure in kPa.
 * \param temp Temperature in deg celsius.
 *
 * \return Refraction angle (rad).
 */
double predict_refraction_from_apparent_ext(double apparent_el, double pressure, double temp);

/*!
 * \brief Calculate refraction rate of change.
 *
 * \param el True elevation angle (rad).
 * \param el_rate Rate of change of true elevation angle (rad/s).
 *
 * \return Refraction rate of change (rad/s).
 */
double predict_refraction_rate(double el, double el_rate);

/*!
 * \brief Calculate refraction rate of change.
 *
 * Corrects for different atmospheric pressure and temerature.
 *
 * \param el True elevation angle (rad).
 * \param el_rate Rate of change of true elevation angle (rad/s).
 * \param pressure Atmospheric pressure in kPa.
 * \param temp Temperature in deg celsius.
 *
 * \return Apparent elevation (rad).
 */
double predict_refraction_rate_ext(double el, double el_rate, double pressure, double temp);

/*!
 * \brief Calculate apparent elevation from true elevation.
 *
 * \param el True elevation angle (rad).
 *
 * \return Apparent elevation (rad).
 */
double predict_apparent_elevation(double el);

/*!
 * \brief Calculate apparent elevation from true elevation.
 *
 * Corrects for different atmospheric pressures and temperatures.
 *
 * \param el True elevation angle (rad).
 * \param pressure Atmospheric pressure (kPa).
 * \param temp Temperature (deg C).
 *
 * \return Apparent elevation (rad).
 */
double predict_apparent_elevation_ext(double el, double pressure, double temp);

/*!
 * \brief Calculate apparent elevation rate.
 *
 * \param el True elevation angle (rad).
 * \param el_rate Rate of change of true elevation angle (rad/s).
 *
 * \return Rate of change of apparent elevation (rad/s).
 */
double predict_apparent_elevation_rate(double el, double el_rate);

/*!
 * \brief Calculate apparent elevation rate.
 *
 * Corrects for different atmospheric pressures and temperatures.
 *
 * \param el True elevation angle (rad).
 * \param el_rate Rate of change of true elevation angle (rad/s).
 * \param pressure Atmospheric pressure (kPa).
 * \param temp Temperature (deg C).
 *
 * \return Rate of change of apparent elevation (rad/s).
 */
double predict_apparent_elevation_rate_ext(double el, double el_rate, double pressure, double temp);

#ifdef __cplusplus
}
#endif

#endif //_PREDICT_H_
