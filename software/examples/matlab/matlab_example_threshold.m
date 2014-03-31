function matlab_example_threshold
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletPTC;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'i4G'; % Change to your UID
    
    ipcon = IPConnection(); % Create IP connection
    ptc = BrickletPTC(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get threshold callbacks with a debounce time of 10 seconds (10000ms)
    ptc.setDebouncePeriod(10000);

    % Register threshold reached callback to function cb_reached
    set(ptc, 'TemperatureReachedCallback', @(h, e)cb_reached(e.temperature));


    % Configure threshold for "greater than 30 °C" (unit is °C/100)
    ptc.setTemperatureCallbackThreshold('>', 30*100, 0);

    input('\nPress any key to exit...\n', 's');
    ipcon.disconnect();
end

% Callback for temperature greater than 30 °C
function cb_reached(temperature)
    fprintf('We have %g °C.\n', temperature/100);
    fprintf('It is too hot, we need air conditioning!\n');
end
