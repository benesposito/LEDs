#ifndef COMM_H
#define COMM_H

#include "state.h"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#endif

#include <stddef.h>

/**
 * @brief communicator interface to read state and send AWK values
 * TODO: write architecture specific classes that are composed of the
 * serial/wifi communication abilities the architecture supports.
 * i.e. comm_arduino has a comm_serial,
 *      comm_esp8266 has a com_serial and comm_wifi
 */
class comm {
public:
    virtual ~comm() = default;

    virtual void update() = 0;
    virtual bool state_available();

    virtual size_t read_state(struct state* state) = 0;
    virtual size_t write_ack(int ack) = 0;

private:
    virtual size_t available() = 0;
};

class comm_serial final : public comm {
public:
    void update();

    size_t read_state(struct state* state);
    size_t write_ack(int ack);

private:
    size_t available();
};

#ifdef ESP8266
/**
 * @brief wireless communicator
 * TODO: implement buffer for packets and read packets in a loop until all are
 * read rather than having to call update() exactly once before read()
 */
class comm_wifi final : public comm {
public:
    comm_wifi();

    /**
     * @brief parse the next packet in the queue. call once and only once prior
     * to calling read()
     */
    void update();

    size_t read_state(struct state* state);
    size_t write_ack(int ack);

    WiFiUDP& udp();

private:
    size_t available();

    WiFiUDP m_udp;
};
#endif

#endif /* COMM_H */