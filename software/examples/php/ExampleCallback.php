<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletPTC.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletPTC;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change to your UID

// Callback function for temperature callback (parameter has unit °C/100)
function cb_temperature($temperature)
{
    echo "Temperature: " . $temperature / 100.0 . " °C\n";
}

$ipcon = new IPConnection(); // Create IP connection
$ptc = new BrickletPTC(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Set Period for temperature callback to 1s (1000ms)
// Note: The callback is only called every second if the 
//       temperature has changed since the last call!
$ptc->setTemperatureCallbackPeriod(1000);

// Register illuminance callback to function cb_temperature
$ptc->registerCallback(BrickletPTC::CALLBACK_TEMPERATURE, 'cb_temperature');

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
