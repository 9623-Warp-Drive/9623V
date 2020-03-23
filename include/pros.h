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

#define PROS_VERSION_MAJOR 3
#define PROS_VERSION_MINOR 2
#define PROS_VERSION_PATCH 1
#define PROS_VERSION_STRING "3.2.1"

#define PROS_ERR (INT32_MAX)
#define PROS_ERR_F (INFINITY)

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#endif  // _PROS_MAIN_H_
