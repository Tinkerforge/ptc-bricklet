#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletPTC;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $ptc = Tinkerforge::BrickletPTC->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current temperature (unit is °C/100)
my $temperature = $ptc->get_temperature();
print "Temperature: " . $temperature/100.0 . " °C\n";

print "Press any key to exit...\n";
<STDIN>;
$ipcon->disconnect();
