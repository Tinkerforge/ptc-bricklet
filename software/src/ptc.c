/* ptc-bricklet
 * Copyright (C) 2012-2013 Olaf Lüke <olaf@tinkerforge.com>
 *
 * poti.c: Implementation of PTC Bricklet messages
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

#include "ptc.h"

#include "bricklib/bricklet/bricklet_communication.h"
#include "bricklib/utility/util_definitions.h"
#include "brickletlib/bricklet_entry.h"
#include "brickletlib/bricklet_simple.h"
#include "bricklib/drivers/adc/adc.h"
#include "config.h"

#define SIMPLE_UNIT_TEMPERATURE 0
#define SIMPLE_UNIT_RESISTANCE 1

// value in 25*°C
/*
import math

def pt100(R, R0=100.0):
    return (-R0 * 3.9083E-3 + math.sqrt(R0 * R0 * + 3.9083E-3 * 3.9083E-3 - 4 * R0 * -5.775E-7 * (R0 - R))) / (2 * R0 * -5.775E-7)

# Debug
#for index, adc_val in enumerate(range(0, (1 << 15) +100, 100)):
#    resistance = adc_val*390.0/(1 << 15)
#    print index, adc_val, resistance, pt100(resistance)

# Code
s = 'const int16_t pt_values[329] = {'
for index, adc_val in enumerate(range(0, (1 << 15) +100, 100)):
    resistance = adc_val*390.0/(1 << 15)
    value = pt100(resistance)
    if index != 0:
        s += ', '
    s += str(int(round(value*25)))
s += '};'

print s
*/
const int16_t pt_values[329] = {-6172, -6101, -6030, -5958, -5887, -5816, -5745, -5673, -5602, -5531, -5459, -5388, -5316, -5244, -5173, -5101, -5029, -4957, -4885, -4813, -4741, -4669, -4597, -4525, -4452, -4380, -4308, -4235, -4163, -4090, -4017, -3945, -3872, -3799, -3726, -3653, -3580, -3507, -3434, -3361, -3287, -3214, -3141, -3067, -2994, -2920, -2847, -2773, -2699, -2625, -2552, -2478, -2404, -2330, -2255, -2181, -2107, -2033, -1958, -1884, -1809, -1735, -1660, -1585, -1511, -1436, -1361, -1286, -1211, -1136, -1061, -986, -910, -835, -759, -684, -608, -533, -457, -381, -306, -230, -154, -78, -2, 75, 151, 227, 304, 380, 456, 533, 610, 686, 763, 840, 917, 994, 1071, 1148, 1225, 1303, 1380, 1458, 1535, 1613, 1690, 1768, 1846, 1924, 2002, 2080, 2158, 2236, 2314, 2392, 2471, 2549, 2628, 2706, 2785, 2864, 2943, 3022, 3101, 3180, 3259, 3338, 3417, 3497, 3576, 3656, 3735, 3815, 3895, 3975, 4054, 4134, 4215, 4295, 4375, 4455, 4536, 4616, 4697, 4777, 4858, 4939, 5020, 5101, 5182, 5263, 5344, 5426, 5507, 5588, 5670, 5752, 5833, 5915, 5997, 6079, 6161, 6243, 6325, 6408, 6490, 6573, 6655, 6738, 6821, 6904, 6987, 7070, 7153, 7236, 7319, 7403, 7486, 7570, 7653, 7737, 7821, 7905, 7989, 8073, 8157, 8241, 8326, 8410, 8495, 8580, 8664, 8749, 8834, 8919, 9004, 9090, 9175, 9260, 9346, 9432, 9517, 9603, 9689, 9775, 9861, 9948, 10034, 10120, 10207, 10293, 10380, 10467, 10554, 10641, 10728, 10815, 10903, 10990, 11078, 11165, 11253, 11341, 11429, 11517, 11605, 11693, 11782, 11870, 11959, 12048, 12137, 12225, 12315, 12404, 12493, 12582, 12672, 12761, 12851, 12941, 13031, 13121, 13211, 13301, 13392, 13482, 13573, 13664, 13755, 13845, 13937, 14028, 14119, 14211, 14302, 14394, 14486, 14578, 14670, 14762, 14854, 14946, 15039, 15132, 15224, 15317, 15410, 15503, 15597, 15690, 15784, 15877, 15971, 16065, 16159, 16253, 16348, 16442, 16537, 16631, 16726, 16821, 16916, 17011, 17107, 17202, 17298, 17394, 17490, 17586, 17682, 17778, 17875, 17971, 18068, 18165, 18262, 18359, 18456, 18554, 18651, 18749, 18847, 18945, 19043, 19141, 19240, 19339, 19437, 19536, 19635, 19734, 19834, 19933, 20033, 20133, 20233, 20333, 20433, 20534, 20634, 20735, 20836, 20937, 21038, 21140, 21241};

const SimpleMessageProperty smp[] = {
	{SIMPLE_UNIT_TEMPERATURE, SIMPLE_TRANSFER_VALUE, SIMPLE_DIRECTION_GET}, // TYPE_GET_TEMPERATURE
	{SIMPLE_UNIT_RESISTANCE, SIMPLE_TRANSFER_VALUE, SIMPLE_DIRECTION_GET}, // TYPE_GET_RESISTANCE
	{SIMPLE_UNIT_TEMPERATURE, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_SET}, // TYPE_SET_TEMPERATURE_CALLBACK_PERIOD
	{SIMPLE_UNIT_TEMPERATURE, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_GET}, // TYPE_GET_TEMPERATURE_CALLBACK_PERIOD
	{SIMPLE_UNIT_RESISTANCE, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_SET}, // TYPE_SET_RESISTANCE_CALLBACK_PERIOD
	{SIMPLE_UNIT_RESISTANCE, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_GET}, // TYPE_GET_RESISTANCE_CALLBACK_PERIOD
	{SIMPLE_UNIT_TEMPERATURE, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_SET}, // TYPE_SET_TEMPERATURE_CALLBACK_THRESHOLD
	{SIMPLE_UNIT_TEMPERATURE, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_GET}, // TYPE_GET_TEMPERATURE_CALLBACK_THRESHOLD
	{SIMPLE_UNIT_RESISTANCE, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_SET}, // TYPE_SET_RESISTANCE_CALLBACK_THRESHOLD
	{SIMPLE_UNIT_RESISTANCE, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_GET}, // TYPE_GET_RESISTANCE_CALLBACK_THRESHOLD
	{0, SIMPLE_TRANSFER_DEBOUNCE, SIMPLE_DIRECTION_SET}, // TYPE_SET_DEBOUNCE_PERIOD
	{0, SIMPLE_TRANSFER_DEBOUNCE, SIMPLE_DIRECTION_GET}, // TYPE_GET_DEBOUNCE_PERIOD
};

const SimpleUnitProperty sup[] = {
	{make_temperature, SIMPLE_SIGNEDNESS_UINT, FID_TEMPERATURE, FID_TEMPERATURE_REACHED, SIMPLE_UNIT_TEMPERATURE}, // temperature
	{make_resistance, SIMPLE_SIGNEDNESS_UINT, FID_RESISTANCE, FID_RESISTANCE_REACHED, SIMPLE_UNIT_RESISTANCE}, // resistance
};

const uint8_t smp_length = sizeof(smp);

void invocation(const ComType com, const uint8_t *data) {
	switch(((SimpleStandardMessage*)data)->header.fid) {
		case FID_SET_NOISE_REJECTION_FILTER: {
			set_noise_rejection_filter(com, (SetNoiseRejectionFilter*)data);
			return;
		}

		case FID_GET_NOISE_REJECTION_FILTER: {
			get_noise_rejection_filter(com, (GetNoiseRejectionFilter*)data);
			return;
		}

		case FID_IS_SENSOR_CONNECTED: {
			is_sensor_connected(com, (IsSensorConnected*)data);
			return;
		}

		case FID_SET_WIRE_MODE: {
			set_wire_mode(com, (SetWireMode*)data);
			return;
		}

		case FID_GET_WIRE_MODE: {
			get_wire_mode(com, (GetWireMode*)data);
			return;
		}

		default: {
			simple_invocation(com, data);
			break;
		}
	}

	if(((SimpleStandardMessage*)data)->header.fid > FID_LAST) {
		BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
	}
}

void constructor(void) {
	_Static_assert(sizeof(BrickContext) <= BRICKLET_CONTEXT_MAX_SIZE, "BrickContext too big");

	SPI_CS.type = PIO_OUTPUT_1;
	SPI_CS.attribute = PIO_DEFAULT;
	BA->PIO_Configure(&SPI_CS, 1);

	SPI_CLK.type = PIO_OUTPUT_1;
	SPI_CLK.attribute = PIO_DEFAULT;
	BA->PIO_Configure(&SPI_CLK, 1);

	SPI_SDI.type = PIO_OUTPUT_1;
	SPI_SDI.attribute = PIO_DEFAULT;
	BA->PIO_Configure(&SPI_SDI, 1);

	SPI_SDO.type = PIO_INPUT;
	SPI_SDO.attribute = PIO_DEFAULT;
	BA->PIO_Configure(&SPI_SDO, 1);

	BC->moving_average_sum = 0;
	BC->moving_average_tick = 0;
	for(uint8_t i = 0; i < NUM_MOVING_AVERAGE; i++) {
		BC->moving_average[i] = 0;
	}

	BC->new_resistance = false;
	BC->noise_filter = 0;
	BC->wire_mode = 2;

	simple_constructor();

	write_register(REG_CONFIGURATION,
	               REG_CONF_50HZ_FILTER);

	BC->current_configuration = REG_CONF_VBIAS_ON |
	                            REG_CONF_50HZ_FILTER |
	                            REG_CONF_CONVERION_MODE_AUTO;

	write_register(REG_CONFIGURATION, BC->current_configuration |
	                                  REG_CONF_FAULT_STATUS_AUTO_CLEAR);
}

void destructor(void) {
	simple_destructor();

	SPI_CS.type = PIO_INPUT;
	SPI_CS.attribute = PIO_DEFAULT;
	BA->PIO_Configure(&SPI_CS, 1);

	SPI_CLK.type = PIO_INPUT;
	SPI_CLK.attribute = PIO_DEFAULT;
	BA->PIO_Configure(&SPI_CLK, 1);

	SPI_SDI.type = PIO_INPUT;
	SPI_SDI.attribute = PIO_DEFAULT;
	BA->PIO_Configure(&SPI_SDI, 1);

	SPI_SDO.type = PIO_INPUT;
	SPI_SDO.attribute = PIO_DEFAULT;
	BA->PIO_Configure(&SPI_SDO, 1);
}

uint8_t spibb_transceive_byte(const uint8_t value) {
	uint8_t recv = 0;

	for(int8_t i = 7; i >= 0; i--) {
		SPI_CLK.pio->PIO_CODR = SPI_CLK.mask;
		if((value >> i) & 1) {
			SPI_SDI.pio->PIO_SODR = SPI_SDI.mask;
		} else {
			SPI_SDI.pio->PIO_CODR = SPI_SDI.mask;
		}

		SLEEP_US(1);
		if(SPI_SDO.pio->PIO_PDSR & SPI_SDO.mask) {
			recv |= (1 << i);
		}

		SPI_CLK.pio->PIO_SODR = SPI_CLK.mask;
		SLEEP_US(1);
	}

	return recv;
}

void write_register(const uint8_t reg, const uint8_t value) {
	SLEEP_US(1);
	SPI_CS.pio->PIO_CODR = SPI_CS.mask;
	spibb_transceive_byte(reg | REG_WRITE);
	spibb_transceive_byte(value);
	SPI_CS.pio->PIO_SODR = SPI_CS.mask;
}

void read_register(const uint8_t reg, uint8_t *data, const uint8_t length) {
	SLEEP_US(1);
	SPI_CS.pio->PIO_CODR = SPI_CS.mask;
	spibb_transceive_byte(reg);
	for(uint8_t i = 1; i <= length; i++) {
		data[length - i] = spibb_transceive_byte(reg + i);
	}
	SPI_CS.pio->PIO_SODR = SPI_CS.mask;
}

int32_t make_resistance(const int32_t value) {
	if((BC->tick % 20) != 0) {
		return value;
	}

	uint16_t resistance = 0;
	read_register(REG_RTD_MSB, (uint8_t*)&resistance, 2);

	if(resistance & REG_RTD_LSB_FAULT) {
		read_register(REG_FAULT_STATUS, &BC->fault, 1);
		write_register(REG_CONFIGURATION, BC->current_configuration |
		                                  REG_CONF_FAULT_STATUS_AUTO_CLEAR);
	} else {
		BC->fault = 0;
	}

	resistance >>= 1;
	if(resistance != value) {
		BC->new_resistance = true;
	}

	return resistance;
}

int32_t make_temperature(const int32_t value) {
	if(!BC->new_resistance) {
		return value;
	}

	BC->new_resistance = false;

	const uint16_t resistance = BC->value[SIMPLE_UNIT_RESISTANCE];

	int16_t rest = resistance % 100;
	int32_t temperature = (pt_values[resistance/100  ]*(100-rest) +
	                       pt_values[resistance/100+1]*(rest    ))/25;

	BC->moving_average_sum = BC->moving_average_sum -
	                         BC->moving_average[BC->moving_average_tick] +
	                         temperature;

	BC->moving_average[BC->moving_average_tick] = temperature;
	BC->moving_average_tick = (BC->moving_average_tick + 1) % NUM_MOVING_AVERAGE;

	return (BC->moving_average_sum + NUM_MOVING_AVERAGE/2)/NUM_MOVING_AVERAGE;
}

void tick(const uint8_t tick_type) {
	simple_tick(tick_type);
}


void set_noise_rejection_filter(const ComType com, const SetNoiseRejectionFilter *data) {
	BC->noise_filter = data->filter;

	if(data->filter == 0) {
		BC->current_configuration |= REG_CONF_50HZ_FILTER;
	} else {
		BC->current_configuration &= ~REG_CONF_50HZ_FILTER;
	}

	// Turn conversion mode off while changing filter
	write_register(REG_CONFIGURATION, BC->current_configuration & (~REG_CONF_CONVERION_MODE_AUTO));
	SLEEP_US(100);

	// Turn conversion mode on again
	write_register(REG_CONFIGURATION, BC->current_configuration);

	BA->com_return_setter(com, data);
}

void get_noise_rejection_filter(const ComType com, const GetNoiseRejectionFilter *data) {
	GetNoiseRejectionFilterReturn gnrfr;

	gnrfr.header        = data->header;
	gnrfr.header.length = sizeof(GetNoiseRejectionFilterReturn);
	gnrfr.filter        = BC->noise_filter;

	BA->send_blocking_with_timeout(&gnrfr, sizeof(GetNoiseRejectionFilterReturn), com);
}

void is_sensor_connected(const ComType com, const IsSensorConnected *data) {
	IsSensorConnectedReturn iscr;

	iscr.header        = data->header;
	iscr.header.length = sizeof(IsSensorConnectedReturn);
	iscr.connected     = BC->fault == 0;

	BA->send_blocking_with_timeout(&iscr, sizeof(IsSensorConnectedReturn), com);
}

void set_wire_mode(const ComType com, const SetWireMode *data) {
	if(data->mode < 2 || data->mode > 4) {
		BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
	}

	BC->wire_mode = data->mode;

	if(data->mode == 3) {
		BC->current_configuration |= REG_CONF_3WIRE_RTD;
	} else {
		BC->current_configuration &= ~REG_CONF_3WIRE_RTD;
	}

	write_register(REG_CONFIGURATION, BC->current_configuration |
	                                  REG_CONF_FAULT_STATUS_AUTO_CLEAR);

	BA->com_return_setter(com, data);
}

void get_wire_mode(const ComType com, const GetWireMode *data) {
	GetWireModeReturn gwmr;

	gwmr.header        = data->header;
	gwmr.header.length = sizeof(GetWireModeReturn);
	gwmr.mode          = BC->wire_mode;

	BA->send_blocking_with_timeout(&gwmr, sizeof(GetWireModeReturn), com);
}
