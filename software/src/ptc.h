/* ptc-bricklet
 * Copyright (C) 2012-2013 Olaf Lüke <olaf@tinkerforge.com>
 *
 * poti.h: Implementation of PTC Bricklet messages
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef PTC_H
#define PTC_H

#include <stdint.h>

#include "bricklib/com/com_common.h"

#define FID_GET_TEMPERATURE 1
#define FID_SET_TEMPERATURE_CALLBACK_PERIOD 2
#define FID_GET_TEMPERATURE_CALLBACK_PERIOD 3
#define FID_SET_TEMPERATURE_CALLBACK_THRESHOLD 4
#define FID_GET_TEMPERATURE_CALLBACK_THRESHOLD 5
#define FID_SET_DEBOUNCE_PERIOD 6
#define FID_GET_DEBOUNCE_PERIOD 7
#define FID_TEMPERATURE 8
#define FID_TEMPERATURE_REACHED 9

#define FID_LAST 9

#define REG_WRITE          0x80


#define REG_CONFIGURATION  0x00
#define REG_RTD_MSB        0x01
#define REG_RTD_LSB        0x02
#define REG_HIGH_FAULT_MSB 0x03
#define REG_HIGH_FAULT_LSB 0x04
#define REG_LOW_FAULT_MSB  0x05
#define REG_LOW_FAULT_LSB  0x06
#define REG_FAULT_STATUS   0x07

#define REG_RTD_LSB_FAULT (1 << 0)

#define REG_CONF_VBIAS_ON (1 << 7)
#define REG_CONF_CONVERION_MODE_AUTO (1 << 6)
#define REG_CONF_ONE_SHOT (1 << 5)
#define REG_CONF_3WIRE_RTD (1 << 4)
#define REG_CONF_FAULT_DETECTION
#define REG_CONF_FAULT_STATUS_AUTO_CLEAR (1 << 1)
#define REG_CONF_50HZ_FILTER (1 << 0)

#define REG_FAULT_RTD_HIGH_THRESHOLD (1 << 7)
#define REG_FAULT_RTD_LOW_THRESHOLD (1 << 6)
#define REG_FAULT_RTD_REFIN (1 << 5)
#define REG_FAULT_RTD_REFIN_FORCE (1 << 4)
#define REG_FAULT_RTD_RTDIN_FORCE (1 << 3)
#define REG_FAULT_OVER_UDER_VOLTAGE (1 << 2)

uint8_t spibb_transceive_byte(const uint8_t value);
int32_t make_temperature(const int32_t value);
void write_register(const uint8_t reg, const uint8_t value);
void read_register(const uint8_t reg, uint8_t *data, const uint8_t length);


void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

#endif
