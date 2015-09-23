using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	// Callback function for temperature reached callback (parameter has unit °C/100)
	static void TemperatureReachedCB(BrickletPTC sender, int temperature)
	{
		Console.WriteLine("Temperature: " + temperature/100.0 + " °C");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletPTC ptc = new BrickletPTC(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
		ptc.SetDebouncePeriod(10000);

		// Register temperature reached callback to function TemperatureReachedCB
		ptc.TemperatureReached += TemperatureReachedCB;

		// Configure threshold for temperature "greater than 30 °C" (unit is °C/100)
		ptc.SetTemperatureCallbackThreshold('>', 30*100, 0);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
