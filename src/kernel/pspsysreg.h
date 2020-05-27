/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsysreg.h - Interface to sceSysreg_driver.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

#ifndef PSPSYSREG_H
#define PSPSYSREG_H

#include <pspkerneltypes.h>

/** @defgroup Sysreg Interface to the sceSysreg_driver library.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Sysreg Interface to the sceSysreg_driver library. */
/*@{*/

/**
  * Enable the ME reset.
  *
  * @return < 0 on error.
  */
int sceSysregMeResetEnable(void);

/**
  * Disable the ME reset.
  *
  * @return < 0 on error.
  */
int sceSysregMeResetDisable(void);

/**
  * Enable the VME reset.
  *
  * @return < 0 on error.
  */
int sceSysregVmeResetEnable(void);

/**
  * Disable the VME reset.
  *
  * @return < 0 on error.
  */
int sceSysregVmeResetDisable(void);

/**
  * Enable the ME bus clock.
  *
  * @return < 0 on error.
  */
int sceSysregMeBusClockEnable(void);

/**
  * Disable the ME bus clock.
  *
  * @return < 0 on error.
  */
int sceSysregMeBusClockDisable(void);

/**
 * Get the PSP's Tachyon version.
 * @param version - A pointer to an int to receive the Tachyon version into
 */
int sceSysconGetTachyonVersion( int* version );

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSPLOADCORE_H */
