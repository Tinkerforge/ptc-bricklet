function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletPTC;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your PTC Bricklet

    ipcon = IPConnection(); % Create IP connection
    ptc = handle(BrickletPTC(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register temperature callback to function cb_temperature
    set(ptc, 'TemperatureCallback', @(h, e) cb_temperature(e));

    % Set period for temperature callback to 1s (1000ms)
    % Note: The temperature callback is only called every second
    %       if the temperature has changed since the last call!
    ptc.setTemperatureCallbackPeriod(1000);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for temperature callback (parameter has unit °C/100)
function cb_temperature(e)
    fprintf('Temperature: %g °C\n', e.temperature/100.0);
end
