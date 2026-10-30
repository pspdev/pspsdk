/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspusbgps.h - Prototypes for the sceUsbGps library
 *
 */
#ifndef __PSPUSBGPS_H__
#define __PSPUSBGPS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <psptypes.h>

#define PSP_USBGPS_PID			(0x283)
#define PSP_USBGPS_DRIVERNAME	"USBGps_Driver"

/** Maximum number of satellites reported in ::SceUsbGpsSatelliteData */
#define PSP_USBGPS_NUM_SATELLITE	(32)

/* Error codes returned by the sceUsbGps functions */
#define PSP_USBGPS_ERROR_NOT_STARTED	(0x80244001)
#define PSP_USBGPS_ERROR_NOT_OPENED		(0x80244002)
#define PSP_USBGPS_ERROR_ALREADY_OPENED	(0x80244003)
#define PSP_USBGPS_ERROR_NOT_AVAILABLE	(0x80244004)
#define PSP_USBGPS_ERROR_BUSY			(0x80244005)
#define PSP_USBGPS_ERROR_PRIV_REQUIRED	(0x80244006)
#define PSP_USBGPS_ERROR_INVALID_PARAM	(0x80244007)
#define PSP_USBGPS_ERROR_FATAL			(0x80244010)
#define PSP_USBGPS_ERROR_NO_INIT_DATA	(0x802440FF)

/** GPS receiver states returned by ::sceUsbGpsGetState */
enum PspUsbGpsState
{
	/** No GPS receiver is connected */
	PSP_USBGPS_STATE_NOT_AVAILABLE = 0,
	/** Something other than a PSP accessory is connected */
	PSP_USBGPS_STATE_NOT_ACCESSORY = 1,
	/** The GPS receiver is initializing */
	PSP_USBGPS_STATE_BUSY = 2,
	/** The GPS receiver is up and running */
	PSP_USBGPS_STATE_WORKING = 3,
};

/** Positioning quality */
enum PspUsbGpsPositionQuality
{
	/** The position cannot be determined */
	PSP_USBGPS_POSITION_QUALITY_NOT_AVAILABLE = 0,
	/** GPS single point positioning */
	PSP_USBGPS_POSITION_QUALITY_GPS = 1,
	/** Differential GPS positioning */
	PSP_USBGPS_POSITION_QUALITY_DGPS = 2,
};

/** Positioning modes */
enum PspUsbGpsPositionMode
{
	/** Positioning cannot be performed */
	PSP_USBGPS_POSITION_MODE_NOT_AVAILABLE = 0,
	/** 2D positioning (latitude/longitude) */
	PSP_USBGPS_POSITION_MODE_2D = 1,
	/** 3D positioning (latitude/longitude/altitude) */
	PSP_USBGPS_POSITION_MODE_3D = 2,
};

/** Satellite usage flags */
enum PspUsbGpsSatelliteFlag
{
	/** The satellite is not used for the position fix */
	PSP_USBGPS_SATELLITE_NOT_USED = 0,
	/** The satellite is used for the position fix */
	PSP_USBGPS_SATELLITE_USED = 1,
};

/** Static navigation modes for ::sceUsbGpsSetStaticNavMode */
enum PspUsbGpsStaticNavMode
{
	PSP_USBGPS_STATIC_NAV_MODE_DISABLE = 0,
	PSP_USBGPS_STATIC_NAV_MODE_ENABLE = 1,
};

/** Storage locations for the GPS init data file, used by
    ::sceUsbGpsSetInitDataLocation and ::sceUsbGpsGetInitDataLocation */
enum PspUsbGpsInitDataLocation
{
	/** flash1:/gps/init_data.bin (default) */
	PSP_USBGPS_INIT_DATA_LOCATION_FLASH1 = 0,
	/** ms0:gps_init_data.bin */
	PSP_USBGPS_INIT_DATA_LOCATION_MS0 = 1,
	/** host0:./gps_init_data.bin */
	PSP_USBGPS_INIT_DATA_LOCATION_HOST0 = 2,
};

/** Power-save modes for ::sceUsbGpsSetPowerSaveMode. Each selects how much the
    receiver sleeps between fixes while the PSP is active vs. idle. Sleeping more
    saves power but reduces the fix frequency. */
enum PspUsbGpsPowerSaveMode
{
	/** No power saving. The receiver tracks continuously at full power. */
	PSP_USBGPS_POWER_SAVE_MODE_OFF          = 0,
	/** Full power when active, sleeps a little between fixes when idle. */
	PSP_USBGPS_POWER_SAVE_MODE_IDLE_LIGHT   = 1,
	/** Full power when active, sleeps a lot between fixes when idle. */
	PSP_USBGPS_POWER_SAVE_MODE_IDLE_DEEP    = 2,
	/** Sleeps a little when active, sleeps a lot when idle. */
	PSP_USBGPS_POWER_SAVE_MODE_MAX          = 3,
	/** Sleeps a little when active, full power when idle. */
	PSP_USBGPS_POWER_SAVE_MODE_ACTIVE_LIGHT = 10,
};

/** Receiver reset levels for ::sceUsbGpsReset, ordered from most to least data
    discarded. Each performs a full receiver restart. They differ only in what
    acquired data is kept. */
enum PspUsbGpsResetType
{
	/** Cold start: discard the ephemeris, almanac, last position and time
	    held in memory. Slowest to get the next fix. */
	PSP_USBGPS_RESET_COLD       = 0,
	/** Warm start: discard ephemeris only, keeping almanac, last position
	    and time. */
	PSP_USBGPS_RESET_WARM       = 1,
	/** Hot start: restart from the position and time retained in the
	    receiver. */
	PSP_USBGPS_RESET_HOT        = 2,
	/** Hot start: restart from the last known position and the current time
	    supplied by the PSP. */
	PSP_USBGPS_RESET_HOT_SEEDED = 3,
};

/** Position information returned by ::sceUsbGpsGetData */
typedef struct SceUsbGpsPositionData {
/** Date and time of the fix (UTC) */
	ScePspDateTime datetime;
/** Horizontal dilution of precision */
	float	hdop;
/** Positioning quality. One of ::PspUsbGpsPositionQuality */
	u8		quality;
/** Positioning mode. One of ::PspUsbGpsPositionMode */
	u8		mode;
/** Reserved */
	u8		reserve0[2];
/** Latitude in degrees, south negative */
	float	latitude;
/** Longitude in degrees, west negative */
	float	longitude;
/** Height above sea level in meters */
	float	altitude;
/** Reserved */
	float	reserve1;
/** Ground speed in km/h */
	float	speed;
/** Direction of travel in degrees */
	float	course;
} SceUsbGpsPositionData;

/** Information about a single GPS satellite */
typedef struct SceUsbGpsSv {
/** Satellite ID */
	u8	id;
/** Angle of elevation in degrees */
	u8	elev;
/** Azimuth in degrees */
	u16	azimuth;
/** Signal-to-noise ratio in dBHz */
	u8	snr;
/** Whether the satellite is used for the fix. One of ::PspUsbGpsSatelliteFlag */
	u8	used;
/** Reserved */
	u8	reserve[2];
} SceUsbGpsSv;

/** Satellite information returned by ::sceUsbGpsGetData */
typedef struct SceUsbGpsSatelliteData {
/** Number of satellites in view */
	u8	num_sv_view;
/** Reserved */
	u8	reserve[3];
/** Details of each satellite in view */
	SceUsbGpsSv	sv_view[PSP_USBGPS_NUM_SATELLITE];
} SceUsbGpsSatelliteData;

/**
 * Initializes the GPS driver and starts GPS receiver operation.
 *
 * The GPS modules have to be loaded with
 * sceUtilityLoadModule(PSP_MODULE_USB_GPS) and the USB bus, accessory
 * and GPS drivers started with ::sceUsbStart before calling this.
 *
 * Available on firmware 2.70 and higher only.
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbGpsOpen(void);

/**
 * Stops GPS receiver operation and shuts down the GPS driver.
 *
 * Available on firmware 2.70 and higher only.
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbGpsClose(void);

/**
 * Gets the state of the GPS receiver.
 *
 * Available on firmware 2.70 and higher only.
 *
 * @param state - pointer to a variable that receives the state,
 * one of ::PspUsbGpsState
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbGpsGetState(u32 *state);

/**
 * Gets position and satellite information.
 *
 * Available on firmware 2.70 and higher only.
 *
 * @param pos - pointer to a structure that receives the position data,
 * or NULL if not needed
 * @param sat - pointer to a structure that receives the satellite data,
 * or NULL if not needed
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbGpsGetData(SceUsbGpsPositionData *pos, SceUsbGpsSatelliteData *sat);

/**
 * Sets the static navigation mode. When enabled, the receiver filters
 * out small movements at low speed to keep the reported position stable.
 * Can be called any time after ::sceUsbGpsOpen. Takes effect immediately
 * if the receiver is running, otherwise when it starts.
 *
 * Available on firmware 3.70 and higher only.
 *
 * @param mode - one of ::PspUsbGpsStaticNavMode
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbGpsSetStaticNavMode(u8 mode);

/**
 * Gets the current static navigation mode.
 *
 * Available on firmware 3.70 and higher only.
 *
 * @param mode - pointer to a variable that receives the mode,
 * one of ::PspUsbGpsStaticNavMode
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbGpsGetStaticNavMode(u8 *mode);

/**
 * Selects the file the GPS init (assistance) data is loaded from when the
 * receiver starts and saved to by ::sceUsbGpsSaveInitData. The default is
 * ::PSP_USBGPS_INIT_DATA_LOCATION_FLASH1. Should be called right after
 * ::sceUsbGpsOpen, before the receiver starts and the file is read.
 *
 * Available on firmware 2.70 and higher only.
 *
 * @param datalocation - one of ::PspUsbGpsInitDataLocation
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbGpsSetInitDataLocation(u32 datalocation);

/**
 * Gets the file currently selected for the GPS init (assistance) data.
 *
 * Available on firmware 2.70 and higher only.
 *
 * @param datalocation - pointer to a variable that receives the current
 * location, one of ::PspUsbGpsInitDataLocation
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbGpsGetInitDataLocation(u32 *datalocation);

/**
 * Saves the GPS init (assistance) data to the file selected with
 * ::sceUsbGpsSetInitDataLocation.
 *
 * The data (last known position, time and ephemeris/almanac) is produced by the
 * receiver while it runs. This call only writes the current in-memory copy to
 * storage so the next session can obtain a fix faster.
 *
 * Available on firmware 2.70 and higher only.
 *
 * @return 0 on success, < 0 on error. Returns PSP_USBGPS_ERROR_NO_INIT_DATA if
 * the receiver has not produced any assistance data yet.
*/
int sceUsbGpsSaveInitData(void);

/**
 * Sets the GPS receiver power-save mode.
 *
 * Power saving engages once the PSP has been idle (no user input) for
 * the given interval, after which the receiver duty-cycles as described by
 * ::PspUsbGpsPowerSaveMode. Should be called immediately after
 * ::sceUsbGpsOpen. It fails once the receiver has started running.
 *
 * Available on firmware 3.00 and higher only.
 *
 * @param mode - one of ::PspUsbGpsPowerSaveMode
 * @param interval - idle time in seconds before power saving engages, 30 to 600
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbGpsSetPowerSaveMode(u32 mode, u32 interval);

/**
 * Gets the current GPS receiver power-save settings.
 *
 * Available on firmware 3.00 and higher only.
 *
 * @param mode - pointer that receives the mode, one of ::PspUsbGpsPowerSaveMode,
 * or NULL if not needed
 * @param interval - pointer that receives the idle time in seconds,
 * or NULL if not needed
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbGpsGetPowerSaveMode(u32 *mode, u32 *interval);

/**
 * Restarts the GPS receiver at the given reset level, controlling how much of
 * its acquired data is discarded.
 *
 * Available on firmware 2.70 and higher only.
 *
 * @param type - one of ::PspUsbGpsResetType
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbGpsReset(u32 type);

/**
 * Seeds the GPS receiver with a known starting position to shorten the time to
 * first fix. Takes effect while the receiver is still searching. It is a no-op
 * once the receiver already has a fix. The receiver is restarted with the new
 * position automatically.
 *
 * The latitude, longitude and altitude can be taken straight from a prior
 * ::sceUsbGpsGetData result. altitude + geoidsep is the WGS84
 * ellipsoidal height. Pass geoidsep as 0 when it is unknown (the
 * resulting error is negligible for a seed).
 *
 * Available on firmware 3.30 and higher only.
 *
 * @param latitude - latitude in degrees, -90 to 90 (south negative)
 * @param longitude - longitude in degrees, -180 to 180 (west negative)
 * @param altitude - height above mean sea level in meters, -10000 to 10000
 * @param geoidsep - geoid-to-ellipsoid separation in meters, -1000 to 1000
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbGpsResetInitialPosition(float latitude, float longitude, float altitude, float geoidsep);

#ifdef __cplusplus
}
#endif

#endif
