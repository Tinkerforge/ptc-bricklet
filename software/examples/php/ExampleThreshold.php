<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletPTC.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletPTC;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your PTC Bricklet

// Callback function for temperature reached callback (parameter has unit °C/100)
function cb_temperatureReached($temperature)
{
    echo "Temperature: " . $temperature/100.0 . " °C\n";
}

$ipcon = new IPConnection(); // Create IP connection
$ptc = new BrickletPTC(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
$ptc->setDebouncePeriod(10000);

// Register temperature reached callback to function cb_temperatureReached
$ptc->registerCallback(BrickletPTC::CALLBACK_TEMPERATURE_REACHED,
                       'cb_temperatureReached');

// Configure threshold for temperature "greater than 30 °C" (unit is °C/100)
$ptc->setTemperatureCallbackThreshold('>', 30*100, 0);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
