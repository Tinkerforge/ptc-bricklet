function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your PTC Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    ptc = javaObject("com.tinkerforge.BrickletPTC", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register temperature callback to function cb_temperature
    ptc.addTemperatureCallback(@cb_temperature);

    % Set period for temperature callback to 1s (1000ms)
    % Note: The temperature callback is only called every second
    %       if the temperature has changed since the last call!
    ptc.setTemperatureCallbackPeriod(1000);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for temperature callback
function cb_temperature(e)
    fprintf("Temperature: %g °C\n", e.temperature/100.0);
end
