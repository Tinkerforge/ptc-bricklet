function octave_example_threshold
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "i4G"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    ptc = java_new("com.tinkerforge.BrickletPTC", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don"t use device before ipcon is connected

    % Get threshold callbacks with a debounce time of 10 seconds (10000ms)
    ptc.setDebouncePeriod(10000);

    % Register threshold reached callback to function cb_reached
    ptc.addTemperatureReachedCallback(@cb_reached);

    % Configure threshold for "greater than 30 °C" (unit is °C/100)
    ptc.setTemperatureCallbackThreshold(">", 30*100, 0);

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

% Callback for temperature greater than 30 °C
function cb_reached(e)
    fprintf("We have %g °C.\n", e.temperature/100.0);
    fprintf("It is too hot, we need air conditioning!\n");
end
