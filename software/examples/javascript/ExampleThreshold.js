var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your PTC Bricklet

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var ptc = new Tinkerforge.BrickletPTC(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Get threshold callbacks with a debounce time of 10 seconds (10000ms)
        ptc.setDebouncePeriod(10000);

        // Configure threshold for temperature "greater than 30 °C"
        ptc.setTemperatureCallbackThreshold('>', 30*100, 0);
    }
);

// Register temperature reached callback
ptc.on(Tinkerforge.BrickletPTC.CALLBACK_TEMPERATURE_REACHED,
    // Callback function for temperature reached callback
    function (temperature) {
        console.log('Temperature: ' + temperature/100.0 + ' °C');
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
