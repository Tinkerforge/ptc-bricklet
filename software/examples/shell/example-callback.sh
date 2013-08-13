#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# set period for temperature callback to 1s (1000ms)
# note: the temperature callback is only called every second if the
#       temperature has changed since the last call!
tinkerforge call ptc-bricklet $uid set-temperature-callback-period 1000

# handle incoming temperature callbacks (unit is °C/100)
tinkerforge dispatch ptc-bricklet $uid temperature
