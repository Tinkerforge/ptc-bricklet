#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_ptc'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your PTC Bricklet

ipcon = IPConnection.new # Create IP connection
ptc = BrickletPTC.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
ptc.set_debounce_period 10000

# Register temperature reached callback (parameter has unit °C/100)
ptc.register_callback(BrickletPTC::CALLBACK_TEMPERATURE_REACHED) do |temperature|
  puts "Temperature: #{temperature/100.0} °C"
end

# Configure threshold for temperature "greater than 30 °C" (unit is °C/100)
ptc.set_temperature_callback_threshold '>', 30*100, 0

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
