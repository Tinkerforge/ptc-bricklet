<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletPTC.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletPTC;

$host = 'localhost';
$port = 4223;
$uid = 'XYZ'; // Change to your UID

// Callback for temperature greater than 30 °C
function cb_reached($temperature)
{
    echo "We have " . $temperature / 100.0 . " °C.\n";
    echo "It is too hot, we need air conditioning!\n";
}

$ipcon = new IPConnection(); // Create IP connection
$ptc = new BrickletPTC($uid, $ipcon); // Create device object

$ipcon->connect($host, $port); // Connect to brickd
// Don't use device before ipcon is connected

// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
$ptc->setDebouncePeriod(10000);

// Register threshold reached callback to function cb_reached
$ptc->registerCallback(BrickletPTC::CALLBACK_TEMPERATURE_REACHED, 'cb_reached');

// Configure threshold for "greater than 30 °C" (unit is °C/100)
$ptc->setTemperatureCallbackThreshold('>', 30*100, 0);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
