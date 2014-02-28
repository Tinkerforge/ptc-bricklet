var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'i33'; // Change to your UID

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var ptc = new Tinkerforge.BrickletPTC(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);
    }
); // Connect to brickd

// Don't use device before ipcon is connected
ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        // Get current temperature (unit is °C/100)
        ptc.getTemperature(
            function(temp) {
                console.log('Temperature: ' + temp/100 + ' °C');
            },
            function(error) {
                console.log('Error: '+error);
            }
        );
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
