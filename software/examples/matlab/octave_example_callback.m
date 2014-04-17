function octave_example_callback
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "i4G"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    ptc = java_new("com.tinkerforge.BrickletPTC", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Set Period for temperature callback to 1s (1000ms)
    % Note: The callback is only called every second if the 
    %       temperature has changed since the last call!
    ptc.setTemperatureCallbackPeriod(1000);

    % Register temperature callback to function cb_temperature
    ptc.addTemperatureCallback(@cb_temperature);

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

% Callback function for temperature callback (parameter has unit °C/100)
function cb_temperature(e)
    fprintf("Temperature: %g °C\n", e.temperature/100.0);
end

