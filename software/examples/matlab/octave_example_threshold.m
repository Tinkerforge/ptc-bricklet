function octave_example_threshold()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your PTC Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    ptc = javaObject("com.tinkerforge.BrickletPTC", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get threshold callbacks with a debounce time of 10 seconds (10000ms)
    ptc.setDebouncePeriod(10000);

    % Register temperature reached callback to function cb_temperature_reached
    ptc.addTemperatureReachedCallback(@cb_temperature_reached);

    % Configure threshold for temperature "greater than 30 °C"
    ptc.setTemperatureCallbackThreshold(">", 30*100, 0);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for temperature reached callback
function cb_temperature_reached(e)
    fprintf("Temperature: %g °C\n", e.temperature/100.0);
end
