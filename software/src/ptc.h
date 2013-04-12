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
#define FID_GET_RESISTANCE 2
#define FID_SET_TEMPERATURE_CALLBACK_PERIOD 3
#define FID_GET_TEMPERATURE_CALLBACK_PERIOD 4
#define FID_SET_RESISTANCE_CALLBACK_PERIOD 5
#define FID_GET_RESISTANCE_CALLBACK_PERIOD 6
#define FID_SET_TEMPERATURE_CALLBACK_THRESHOLD 7
#define FID_GET_TEMPERATURE_CALLBACK_THRESHOLD 8
#define FID_SET_RESISTANCE_CALLBACK_THRESHOLD 9
#define FID_GET_RESISTANCE_CALLBACK_THRESHOLD 10
#define FID_SET_DEBOUNCE_PERIOD 11
#define FID_GET_DEBOUNCE_PERIOD 12
#define FID_TEMPERATURE 13
#define FID_TEMPERATURE_REACHED 14
#define FID_RESISTANCE 15
#define FID_RESISTANCE_REACHED 16
#define FID_SET_NOISE_REJECTION_FILTER 17
#define FID_GET_NOISE_REJECTION_FILTER 18
#define FID_IS_SENSOR_CONNECTED 19
#define FID_SET_WIRE_MODE 20
#define FID_GET_WIRE_MODE 21

#define FID_LAST 21

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

typedef struct {
	MessageHeader header;
	uint8_t filter;
} __attribute__((__packed__)) SetNoiseRejectionFilter;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetNoiseRejectionFilter;

typedef struct {
	MessageHeader header;
	uint8_t filter;
} __attribute__((__packed__)) GetNoiseRejectionFilterReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) IsSensorConnected;

typedef struct {
	MessageHeader header;
	bool connected;
} __attribute__((__packed__)) IsSensorConnectedReturn;

typedef struct {
	MessageHeader header;
	uint8_t mode;
} __attribute__((__packed__)) SetWireMode;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetWireMode;

typedef struct {
	MessageHeader header;
	uint8_t mode;
} __attribute__((__packed__)) GetWireModeReturn;

void set_noise_rejection_filter(const ComType com, const SetNoiseRejectionFilter *data);
void get_noise_rejection_filter(const ComType com, const GetNoiseRejectionFilter *data);
void is_sensor_connected(const ComType com, const IsSensorConnected *data);
void set_wire_mode(const ComType com, const SetWireMode *data);
void get_wire_mode(const ComType com, const GetWireMode *data);


uint8_t spibb_transceive_byte(const uint8_t value);
int32_t make_temperature(const int32_t value);
int32_t make_resistance(const int32_t value);
void write_register(const uint8_t reg, const uint8_t value);
void read_register(const uint8_t reg, uint8_t *data, const uint8_t length);


void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

#endif
