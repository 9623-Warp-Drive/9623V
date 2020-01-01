/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2019, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#ifdef __cplusplus
#include <cerrno>
#include <cmath>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#else /* (not) __cplusplus */
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#endif /* __cplusplus */

#define PROS_VERSION_MAJOR 3
#define PROS_VERSION_MINOR 2
#define PROS_VERSION_PATCH 0
#define PROS_VERSION_STRING "3.2.0"

#define PROS_ERR (INT32_MAX)
#define PROS_ERR_F (INFINITY)

#include "pros/adi.h"
#include "pros/colors.h"
#include "pros/llemu.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "pros/vision.h"

#ifdef __cplusplus
#include "pros/adi.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.hpp"
#include "okapi/api.hpp"
#endif

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#endif  // _PROS_MAIN_H_
