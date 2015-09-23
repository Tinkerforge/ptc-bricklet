function matlab_example_threshold()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletPTC;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    ptc = BrickletPTC(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get threshold callbacks with a debounce time of 10 seconds (10000ms)
    ptc.setDebouncePeriod(10000);

    % Register temperature reached callback to function cb_temperature_reached
    set(ptc, 'TemperatureReachedCallback', @(h, e) cb_temperature_reached(e));

    % Configure threshold for temperature "greater than 30 °C" (unit is °C/100)
    ptc.setTemperatureCallbackThreshold('>', 30*100, 0);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for temperature reached callback (parameter has unit °C/100)
function cb_temperature_reached(e)
    fprintf('Temperature: %g °C\n', e.temperature/100.0);
end
