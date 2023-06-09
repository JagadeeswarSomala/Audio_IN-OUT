#ifndef __BLE_INIT__
#define __BLE_INIT__

#include <Arduino.h>

#define BLE_RX_BUFFER_SIZE 64
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
// #include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void ble_init(const char *device_name);

#endif