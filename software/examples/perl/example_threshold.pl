#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletPTC;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your PTC Bricklet

# Callback subroutine for temperature reached callback
sub cb_temperature_reached
{
    my ($temperature) = @_;

    print "Temperature: " . $temperature/100.0 . " °C\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $ptc = Tinkerforge::BrickletPTC->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
$ptc->set_debounce_period(10000);

# Register temperature reached callback to subroutine cb_temperature_reached
$ptc->register_callback($ptc->CALLBACK_TEMPERATURE_REACHED, 'cb_temperature_reached');

# Configure threshold for temperature "greater than 30 °C"
$ptc->set_temperature_callback_threshold('>', 30*100, 0);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
