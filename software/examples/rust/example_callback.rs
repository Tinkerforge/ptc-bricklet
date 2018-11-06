use std::{error::Error, io, thread};
use tinkerforge::{ipconnection::IpConnection, ptc_bricklet::*};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your PTC Bricklet

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let ptc_bricklet = PTCBricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    //Create listener for temperature events.
    let temperature_listener = ptc_bricklet.get_temperature_receiver();
    // Spawn thread to handle received events. This thread ends when the ptc_bricklet
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for event in temperature_listener {
            println!("Temperature: {}{}", event as f32 / 100.0, " °C");
        }
    });

    // Set period for temperature listener to 1s (1000ms)
    // Note: The temperature callback is only called every second
    //       if the temperature has changed since the last call!
    ptc_bricklet.set_temperature_callback_period(1000);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
