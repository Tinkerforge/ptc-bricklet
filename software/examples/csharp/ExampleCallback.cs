using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your PTC Bricklet

	// Callback function for temperature callback (parameter has unit °C/100)
	static void TemperatureCB(BrickletPTC sender, int temperature)
	{
		Console.WriteLine("Temperature: " + temperature/100.0 + " °C");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletPTC ptc = new BrickletPTC(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register temperature callback to function TemperatureCB
		ptc.Temperature += TemperatureCB;

		// Set period for temperature callback to 1s (1000ms)
		// Note: The temperature callback is only called every second
		//       if the temperature has changed since the last call!
		ptc.SetTemperatureCallbackPeriod(1000);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
