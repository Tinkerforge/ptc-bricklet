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

	// Get current temperature.
	temperature, _ := ptc.GetTemperature()
	fmt.Printf("Temperature: %f °C\n", float64(temperature)/100.0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
