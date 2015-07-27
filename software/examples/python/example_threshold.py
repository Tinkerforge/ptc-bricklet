#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_ptc import PTC

# Callback function for temperature greater than 120 °C (parameter has unit °C/100)
def cb_temperature_reached(temperature):
    print('Temperature: ' + str(temperature/100.0) + ' °C')

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    ptc = PTC(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Get threshold callbacks with a debounce time of 10 seconds (10000ms)
    ptc.set_debounce_period(10000)

    # Register threshold reached callback to function cb_temperature_reached
    ptc.register_callback(ptc.CALLBACK_TEMPERATURE_REACHED, cb_temperature_reached)

    # Configure threshold for "greater than 120 °C" (unit is °C/100)
    ptc.set_temperature_callback_threshold('>', 120*100, 0)

    raw_input('Press key to exit\n') # Use input() in Python 3
    ipcon.disconnect()
