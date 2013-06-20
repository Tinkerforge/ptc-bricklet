
#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_ptc.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

// Callback function for temperature callback (parameter has unit °C/100)
void cb_temperature(int32_t temperature, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Temperature: %f °C.\n", temperature/100.0);
}

int main() {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	PTC ptc;
	ptc_create(&ptc, UID, &ipcon); 

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}
	// Don't use device before ipcon is connected

	// Set Period for temperature callback to 1s (1000ms)
	// Note: The callback is only called every second if the 
	//       temperature has changed since the last call!
	ptc_set_temperature_callback_period(&ptc, 1000);

	// Register temperature callback to function cb_temperature
	ptc_register_callback(&ptc,
	                      PTC_CALLBACK_TEMPERATURE, 
	                      (void *)cb_temperature,
	                      NULL);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}
