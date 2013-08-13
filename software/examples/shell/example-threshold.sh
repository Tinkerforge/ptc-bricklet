#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# get threshold callbacks with a debounce time of 10 seconds (10000ms)
tinkerforge call ptc-bricklet $uid set-debounce-period 10000

# configure threshold for "greater than 30 °C" (unit is °C/100)
tinkerforge call ptc-bricklet $uid set-illuminance-callback-threshold greater 3000 0

# handle incoming temperature-reached callbacks (unit is °C/100)
tinkerforge dispatch ptc-bricklet $uid temperature-reached\
 --execute "echo We have {temperature} °C/100. It is too hot, we need air conditioning!"
