package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
	"github.com/Tinkerforge/go-api-bindings/ptc_bricklet"
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

	// Get threshold receivers with a debounce time of 10 seconds (10000ms).
	ptc.SetDebouncePeriod(10000)

	ptc.RegisterTemperatureReachedCallback(func(temperature int32) {
		fmt.Printf("Temperature: %f °C\n", float64(temperature)/100.0)
	})

	// Configure threshold for temperature "greater than 30 °C".
	ptc.SetTemperatureCallbackThreshold('>', 30*100, 0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
