#include <Arduino.h>
#include "ble_init.h"

void setup()
{
	Serial.begin(115200);

	ble_init("Pebbl_BLE");
}

void loop()
{
	// Serial.println("L");
	// delay(2000);
}