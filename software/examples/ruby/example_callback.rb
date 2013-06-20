#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_ptc'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change to your UID

ipcon = IPConnection.new # Create IP connection
ptc = BrickletPTC.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Set Period for temperature callback to 1s (1000ms)
# Note: The callback is only called every second if the 
#       temperature has changed since the last call!
ptc.set_temperature_callback_period 1000 

# Register temperature callback (parameter has unit °C/100)
ptc.register_callback(BrickletPTC::CALLBACK_TEMPERATURE) do |temperature|
  puts "Temperature: #{temperature/100.0} °C"
end

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
