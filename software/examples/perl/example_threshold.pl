#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletPTC;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $ptc = Tinkerforge::BrickletPTC->new(&UID, $ipcon); # Create device object

# Callback subroutine for temperature greater than 120 °C (parameter has unit °C/100)
sub cb_temperature_reached
{
    my ($temperature) = @_;

    print "Temperature: " . $temperature/100.0 . " °C\n";
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
$ptc->set_debounce_period(10000);

# Register threshold reached callback to subroutine cb_temperature_reached
$ptc->register_callback($ptc->CALLBACK_TEMPERATURE_REACHED, 'cb_temperature_reached');

# Configure threshold for "greater than 120 °C" (unit is °C/100)
$ptc->set_temperature_callback_threshold('>', 120*100, 0);

print "Press any key to exit...\n";
<STDIN>;
$ipcon->disconnect();
