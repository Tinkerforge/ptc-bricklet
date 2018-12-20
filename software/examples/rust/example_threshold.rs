use std::{io, error::Error};
use std::thread;
use tinkerforge::{ip_connection::IpConnection, 
                  ptc_bricklet::*};


const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your PTC Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let ptc = PtcBricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
    // Don't use device before ipcon is connected.

		// Get threshold receivers with a debounce time of 10 seconds (10000ms).
		ptc.set_debounce_period(10000);

     let temperature_reached_receiver = ptc.get_temperature_reached_callback_receiver();

        // Spawn thread to handle received callback messages. 
        // This thread ends when the `ptc` object
        // is dropped, so there is no need for manual cleanup.
        thread::spawn(move || {
            for temperature_reached in temperature_reached_receiver {           
                		println!("Temperature: {} °C", temperature_reached as f32 /100.0);
            }
        });

		// Configure threshold for temperature "greater than 30 °C".
		ptc.set_temperature_callback_threshold('>', 30*100, 0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
