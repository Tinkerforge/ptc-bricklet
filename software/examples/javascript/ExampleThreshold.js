var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'i33';// Change to your UID

var ipcon = new Tinkerforge.IPConnection();// Create IP connection
var ptc = new Tinkerforge.BrickletPTC(UID, ipcon);// Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);        
    }
);// Connect to brickd

// Don't use device before ipcon is connected
ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        // Get threshold callbacks with a debounce time of 10 seconds (10000ms)
        ptc.setDebouncePeriod(10000);
        // Configure threshold for "greater than 30 °C" (unit is °C/100)
        ptc.setTemperatureCallbackThreshold('>', 30*100, 0);
    }
);

// Register threshold reached callback
ptc.on(Tinkerforge.BrickletPTC.CALLBACK_TEMPERATURE_REACHED,
    // Callback for temperature greater than 30 °C
    function(temp) {
        console.log('We have ' + temp/100.0+' °C.');
        console.log('It is too hot, we need air conditioning!');
        console.log();
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);

