using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	// Callback for temperature greater than 30 °C
	static void ReachedCB(BrickletPTC sender, int temperature)
	{
		System.Console.WriteLine("We have: " + temperature/100.0 + " °C");
		System.Console.WriteLine("It is too hot, we need air conditioning!");
	}

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletPTC ptc = new BrickletPTC(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
		ptc.SetDebouncePeriod(10000);

		// Register threshold reached callback to function ReachedCB
		ptc.TemperatureReached += ReachedCB;

		// Configure threshold for "greater than 30 °C" (unit is °C/100)
		ptc.SetTemperatureCallbackThreshold('>', 30*100, 0);

		System.Console.WriteLine("Press enter to exit");
		System.Console.ReadLine();
		ipcon.Disconnect();
	}
}
