#include "comm.h"

#include <Arduino.h>
#include <EEPROM.h>

void comm::begin() {}

int comm::status() { return 0; }
bool comm::ready() { return true; }

bool comm::state_available() { return available() == sizeof(struct state); }

void comm::clear_read_buffer() {
    while (available()) {
        read();
    }
}

void comm_serial::update() {}
size_t comm_serial::available() { return Serial.available(); }

size_t comm_serial::read_state(struct state* state) {
    return Serial.readBytes(reinterpret_cast<uint8_t*>(state), sizeof(*state));
}

size_t comm_serial::write_ack(int ack) { return Serial.write(ack); }

int comm_serial::read() { return Serial.read(); }

/**
 * TODO: better system for conditionally compiling comm_wifi
 * hopefully I can find a way to selectively compile a 'comm_wifi.cpp' file
 */
#ifdef ESP8266
struct wifi_config {
    char ssid[32];
    char password[32];
};

void comm_wifi::begin() {
    struct wifi_config config;

    EEPROM.begin(sizeof(struct wifi_config));
    EEPROM.get(0, config);
    EEPROM.end();

    WiFi.begin(config.ssid, config.password);
    m_udp.begin(1111);
}

int comm_wifi::status() { return WiFi.status(); }
bool comm_wifi::ready() { return status() == WL_CONNECTED; }

void comm_wifi::update() { m_udp.parsePacket(); }
size_t comm_wifi::available() { return m_udp.available(); }

size_t comm_wifi::read_state(struct state* state) {
    return m_udp.read(reinterpret_cast<uint8_t*>(state), sizeof(*state));
}

size_t comm_wifi::write_ack(int ack) {
    m_udp.beginPacket(m_udp.remoteIP(), m_udp.remotePort());
    size_t ret = m_udp.write(reinterpret_cast<uint8_t*>(&ack), sizeof(ack));
    m_udp.endPacket();

    return ret;
}

int comm_wifi::read() { return m_udp.read(); }

IPAddress comm_wifi::ip() { return WiFi.localIP(); }
WiFiUDP& comm_wifi::udp() { return m_udp; }
#endif