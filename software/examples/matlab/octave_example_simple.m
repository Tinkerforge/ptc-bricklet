function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your PTC Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    ptc = javaObject("com.tinkerforge.BrickletPTC", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current temperature (unit is °C/100)
    temperature = ptc.getTemperature();
    fprintf("Temperature: %g °C\n", temperature/100.0);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
