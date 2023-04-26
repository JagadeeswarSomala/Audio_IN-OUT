#include "ble_init.h"

static BLECharacteristic *pCharacteristic;
// static BLEService *pService;

class ble_server_cb_events : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        Serial.println("BLE: Client Connected");
        pCharacteristic->setValue("BLE_CONNECTED");
    }

    void onDisconnect(BLEServer *pServer)
    {
        Serial.println("BLE: Client Disconnected");      

        BLEDevice::startAdvertising();
    }
};

class ble_char_cb_events : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic* pCharacteristic, esp_ble_gatts_cb_param_t* param)
    {
        if(param->write.len > 0 && param->write.len <= 64)
        {
            Serial.printf("Length: %d\n",param->write.len);

            char *recv_data = (char *) calloc(1, param->write.len + 1);
            strncpy(recv_data, (const char *) param->write.value, param->write.len);

            Serial.printf("BLE: Data Received = %s\n", recv_data);

            if(strcmp(recv_data, "OKAY") == 0)
            {
                // Serial.println("STRCMP = 0");
                pCharacteristic->setValue("BLE_CONNECTED");
                // pCharacteristic->notify();
            }

            free(recv_data);
            recv_data = NULL;
        }
        else
        {
            Serial.printf("Length: %d\n",param->write.len);
            Serial.println("BLE: Data length should be <= 64");
        }
    }
};

void ble_init(const char *device_name)
{
    BLEDevice::init(device_name);
    BLEDevice::setMTU(64); // By default we can send only 20 bytes. Using setMTU we are changing it to 64

    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new ble_server_cb_events);

    BLEService *pService = pServer->createService(SERVICE_UUID);

    pCharacteristic = pService->createCharacteristic(
                                                        CHARACTERISTIC_UUID,
                                                        BLECharacteristic::PROPERTY_READ    |
                                                        BLECharacteristic::PROPERTY_WRITE   |
                                                        BLECharacteristic::PROPERTY_NOTIFY  |
                                                        BLECharacteristic::PROPERTY_INDICATE
                                                    );

    // pCharacteristic->addDescriptor(new BLE2902());
    pCharacteristic->setCallbacks(new ble_char_cb_events);
    
    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);

    BLEDevice::startAdvertising();
    Serial.printf("Now you can connect to %s\n", device_name);
}