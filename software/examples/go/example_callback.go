package main

import (
	"fmt"
	"github.com/tinkerforge/go-api-bindings/ipconnection"
	"github.com/tinkerforge/go-api-bindings/ptc_bricklet"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your PTC Bricklet.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	ptc, _ := ptc_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	ptc.RegisterTemperatureCallback(func(temperature int32) {
		fmt.Printf("Temperature: %f °C\n", float64(temperature)/100.0)
	})

	// Set period for temperature receiver to 1s (1000ms).
	// Note: The temperature callback is only called every second
	//       if the temperature has changed since the last call!
	ptc.SetTemperatureCallbackPeriod(1000)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
