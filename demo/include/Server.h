#pragma once

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <fcntl.h>

#include <vector>
#include <optional>
#include <iostream>

#include <unistd.h>

#include "Utilities.h"


#define PACKET_SIZE 256
// TODO consexpr

using u32 = unsigned int;
using u16 = unsigned short;
using u8 = unsigned char;

struct Address {
    Address() = default;
    Address(u32 a, u32 b, u32 c, u32 d, u16 port);
    Address(u32 ip, u16 port);
    u32 a, b, c, d;
    u16 port_;
    u32 ip() const;
    u16 port() const;
};

class Socket {
public:
    Socket(u16 port);
    // ~Socket(); // TODO
    bool send(const Address &dest, const char *data, int dataSize = PACKET_SIZE);
    bool receive(Address &sender, char *data, int maxDataSize = PACKET_SIZE);

private:
    int sock_;
    u16 port_;
};

class InternetConnection { // TODO move socket here and functions
public:
    virtual int connect(const Address &) = 0;
    virtual void receive(int dataMaxSize = PACKET_SIZE) = 0;
    virtual void send(const char *data, int dataSize = PACKET_SIZE) = 0;
    void setPress(const std::function<void(Utilities::Direction)>& f);
    void setRelease(const std::function<void(Utilities::Direction)>& f);
    static std::vector<char> buildPacket(bool isPressed, Utilities::Direction dir);

protected:
    std::function<void(Utilities::Direction)> press;
    std::function<void(Utilities::Direction)> release;
};

class Server : public InternetConnection {
public:
    explicit Server(u16 port = 5051); // 5051 - порт сервера
    int connect(const Address &addr) override; // returns id
    void receive(int dataMaxSize = PACKET_SIZE) override; // хэндлим прям там
    void send(const char *data, int dataSize = PACKET_SIZE) override;

private:
    Socket socket_;
    std::vector<Address> connections_;
};

class Client : public InternetConnection {
public:
    Client(u16 serverPort = 5051, u16 myPort = 5052);
    int connect(const Address &addr) override;
    void receive(int dataMaxSize = PACKET_SIZE) override;
    void send(const char *data, int dataSize = PACKET_SIZE) override;

private:
    Socket socket_;
    Address server_;
};
