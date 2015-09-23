#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change to your UID

# Get current temperature (unit is °C/100)
tinkerforge call ptc-bricklet $uid get-temperature
