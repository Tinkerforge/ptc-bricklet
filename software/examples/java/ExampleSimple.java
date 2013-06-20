import com.tinkerforge.BrickletPTC;
import com.tinkerforge.IPConnection;

public class ExampleSimple {
	private static final String host = "localhost";
	private static final int port = 4223;
	private static final String UID = "XYZ"; // Change to your UID
	
	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletPTC ptc = new BrickletPTC(UID, ipcon); // Create device object

		ipcon.connect(host, port); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get current temperature (unit is °C/100)
		int temperature = ptc.getTemperature(); // Can throw com.tinkerforge.TimeoutException

		System.out.println("Temperature: " + temperature/100.0 + " °C");

		System.console().readLine("Press key to exit\n");
		ipcon.disconnect();
	}
}
