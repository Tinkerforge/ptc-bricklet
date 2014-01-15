<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletPTC.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletPTC;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change to your UID

$ipcon = new IPConnection(); // Create IP connection
$ptc = new BrickletPTC(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current temperature (unit is °C/100)
$temperature = $ptc->getTemperature() / 100.0;

echo "Temperature: $temperature °C\n";

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
