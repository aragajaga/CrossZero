#ifndef GAMERULE_HPP
#define GAMERULE_HPP

#define MARK_EMPTY  0
#define MARK_CROSS  1
#define MARK_CIRCLE 2

#define PACKET_TURN             0x01
#define PACKET_OPPONENTWAIT     0x02
#define PACKET_OPPONENTREADY    0x03

struct GameSettings {
    unsigned int screen_w;
    unsigned int screen_h;

    uint8_t antialiasing_level;
    unsigned int framerate_limit;
    bool vsync;

    std::string server_ip;
    unsigned int server_port;
};

#endif
