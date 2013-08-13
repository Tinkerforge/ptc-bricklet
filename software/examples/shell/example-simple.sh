#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# get current temperature (unit is °C/100)
tinkerforge call ptc-bricklet $uid get-temperature
