#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your PTC Bricklet

# Get current temperature
tinkerforge call ptc-bricklet $uid get-temperature
