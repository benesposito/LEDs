#include "comm.h"

#include <Arduino.h>
#include <EEPROM.h>

struct wifi_config {
    char ssid[32];
    char password[32];
};

bool comm::state_available() { return available() == sizeof(struct state); }

void comm_serial::update() {}
size_t comm_serial::available() { return Serial.available(); }

size_t comm_serial::read_state(struct state* state) {
    return Serial.readBytes(reinterpret_cast<uint8_t*>(state), sizeof(*state));
}

size_t comm_serial::write_ack(int ack) { return Serial.write(ack); }

/**
 * TODO: better system for conditionally compiling comm_wifi
 * hopefully I can find a way to selectively compile a 'comm_wifi.cpp' file
 */
#ifdef ESP8266
comm_wifi::comm_wifi() {
    struct wifi_config config;

    EEPROM.begin(sizeof(struct wifi_config));
    EEPROM.get(0, config);

    WiFi.begin(config.ssid, config.password);

    while (WiFi.status() != WL_CONNECTED) {
        char output[64];
        snprintf(output, sizeof(output), "Connecting... [%d]\n", WiFi.status());
        Serial.print(output);
        delay(500);
    }

    m_udp.begin(1111);
    Serial.println("Connected!");
    Serial.println(WiFi.localIP());
}

void comm_wifi::update() { m_udp.parsePacket(); }
size_t comm_wifi::available() { return m_udp.available(); }

size_t comm_wifi::read_state(struct state* state) {
    return m_udp.read(reinterpret_cast<uint8_t*>(state), sizeof(*state));
}

size_t comm_wifi::write_ack(int ack) {
    m_udp.beginPacket(m_udp.remoteIP(), m_udp.remotePort());
    size_t ret = m_udp.write(ack);
    m_udp.endPacket();

    return ret;
}

WiFiUDP& comm_wifi::udp() { return m_udp; }
#endif