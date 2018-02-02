#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletPTC;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your PTC Bricklet

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $ptc = Tinkerforge::BrickletPTC->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current temperature
my $temperature = $ptc->get_temperature();
print "Temperature: " . $temperature/100.0 . " °C\n";

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
