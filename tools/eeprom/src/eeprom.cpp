#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

struct wifi_config {
    char ssid[32];
    char password[32];
    char hostname[32];
};

void write_eeprom();
void read_eeprom();
void wifi_connect();

void setup() {
    Serial.begin(9600);
    EEPROM.begin(sizeof(wifi_config));

#ifdef EEPROM_WRITE
    write_eeprom();
#endif

    read_eeprom();
    wifi_connect();
}

#ifdef EEPROM_WRITE
void write_eeprom() {
    struct wifi_config config;
    strncpy(config.ssid, EEPROM_SSID, sizeof(config.ssid));
    strncpy(config.password, EEPROM_PASSWORD, sizeof(config.password));
    strncpy(config.hostname, EEPROM_HOSTNAME, sizeof(config.hostname));

    EEPROM.put(0, config);
    EEPROM.commit();
}
#endif

void read_eeprom() {
    struct wifi_config config;
    EEPROM.get(0, config);

    Serial.println(config.ssid);
    Serial.println(config.password);
    Serial.println(config.hostname);
}

void loop() {}

void wifi_connect() {
    struct wifi_config config;
    EEPROM.get(0, config);

    WiFi.hostname(config.hostname);
    WiFi.begin(config.ssid, config.password);

    size_t last_print = 0;
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - last_print > 500) {
            char output[64];
            snprintf(output, sizeof(output), "Connecting... [%d]\n",
                     WiFi.status());
            Serial.print(output);
            last_print = millis();
        }
    }

    Serial.println("Connected");
}
