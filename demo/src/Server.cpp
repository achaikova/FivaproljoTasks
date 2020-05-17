#include <cassert>
#include "Server.h"

Address::Address(u32 a, u32 b, u32 c, u32 d, u16 port)
    : a(a)
    , b(b)
    , c(c)
    , d(d)
    , port_(port)
{}

Address::Address(u32 ip, u16 port)
    : port_(port) {
    u32 mask = ~static_cast<u8>(0);
    d = ip & mask;
    mask <<= 8;
    c = ip & mask;
    mask <<= 8;
    b = ip & mask;
    mask <<= 8;
    a = ip & mask;
}

u32 Address::ip() const {
    return (a << 24) | (b << 16) | (c << 8) | d;
}

u16 Address::port() const {
    return port_;
}

Socket::Socket(u16 port)
    : sock_(socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))
    , port_(port) {
    assert(sock_ > 0);

    sockaddr_in sockAddress;
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_addr.s_addr = INADDR_ANY;
    sockAddress.sin_port = htons(static_cast<u16>(port_));

    int res = bind(sock_, (sockaddr *)&sockAddress, sizeof(sockAddress)); // TODO reinterpret
    assert(res >= 0);
    
    res = fcntl(sock_, F_SETFL, O_NONBLOCK, 1);
    assert(res != -1);
}

bool Socket::send(const Address &dest, const char *data, int dataSize) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(dest.ip());
    addr.sin_port = htons(dest.port());
    int sentBytes = sendto(sock_, data, dataSize, 0, (sockaddr *)&addr, sizeof(addr));
    return sentBytes == dataSize;
}

bool Socket::receive(Address& sender, char *data, int maxDataSize) {
    sockaddr_in from;
    socklen_t fromLen = sizeof(from);
    int receivedBytes = recvfrom(sock_, data, maxDataSize, 0, (sockaddr *)&from, &fromLen);
    sender = Address(ntohl(from.sin_addr.s_addr), ntohl(from.sin_port));
    return receivedBytes == maxDataSize;
}

void InternetConnection::setPress(const std::function<void(Utilities::Direction)>& f) {
    press = f;
}

void InternetConnection::setRelease(const std::function<void(Utilities::Direction)>& f) {
    release = f;
}

Server::Server(u16 port) : socket_(port) {}

int Server::connect(const Address& addr) {
    connections_.push_back(addr);
    // видимо какую-то начальную посылку
    return connections_.size() - 1;
}

/*
 * Тут kinda документация к тому, какие пакеты перекидываются, и что они делают и вообещпывлиыволрмифвылодмв
 * В будущем планируется, что тут будет проверка того, что все пакеты дошли, но это потом
 * По глубинам байт:
 *   0 | 1 | 2...
 * | 0 | - начальный коммит, его пока нет
 * | 1 | - кнопка нажата
 * * * | 1 | - нажата кнопка "Вверх"
 * * * | 2 | - нажата кнопка "Влево"
 * * * | 3 | - нажата кнопка "Вниз"
 * * * | 4 | - нажата кнопка "Вправо
 * | 2 | - кнопка отпущена 
 * * * | 1 | - отпущена кнопка "Вверх"
 * * * | 2 | - отпущена кнопка "Влево"
 * * * | 3 | - отпущена кнопка "Вниз"
 * * * | 4 | - отпущена кнопка "Вправо
 * | 3 | - id игрока, пока все id считаются равными 1, ибо пока пилю под 2 игрока // TODO сдвинуть все, чтобы это было 1
 * Впилить сюда меню
 */

void Server::receive(int dataMaxSize) { // TODO получив, разослать всем, но пока 2 игрока - не нужно
    char packet[dataMaxSize];
    Address sender;
    if (socket_.receive(sender, packet)) {
        if (packet[0] == 0) { // init
	    // :(
        } else if (packet[0] == 1) { // pressed
	    if (InternetConnection::press) {
                if (packet[1] == 1) { // UP
                    InternetConnection::press(Utilities::Direction::UP);
                } else if (packet[1] == 2) { // LEFT 
                    InternetConnection::press(Utilities::Direction::LEFT);
                } else if (packet[1] == 3) { // DOWN 
                    InternetConnection::press(Utilities::Direction::DOWN);
                } else if (packet[1] == 4) { // RIGHT 
                    InternetConnection::press(Utilities::Direction::RIGHT);
                }
	    }
        } else if (packet[0] == 2) { // released	    
	    if (InternetConnection::release) {
                if (packet[1] == 1) { // UP
                    InternetConnection::release(Utilities::Direction::UP);
                } else if (packet[1] == 2) { // LEFT 
                    InternetConnection::release(Utilities::Direction::LEFT);
                } else if (packet[1] == 3) { // DOWN 
                    InternetConnection::release(Utilities::Direction::DOWN);
                } else if (packet[1] == 4) { // RIGHT 
                    InternetConnection::release(Utilities::Direction::RIGHT);
                }
	    }
	}
    } else {
        // ну, по факту тут ниче делать не надо будет
    }
}

std::vector<char> InternetConnection::buildPacket(bool isPressed, Utilities::Direction dir) { //!pressed=rlsed TODO enum
    std::vector<char> packet(256, 0);
    if (isPressed) {
        packet[0] = 1;
    } else {
        packet[0] = 2;
    }
    if (dir == Utilities::Direction::UP) {
        packet[1] = 1;
    } else 
    if (dir == Utilities::Direction::LEFT) {
        packet[1] = 2;
    } else 
    if (dir == Utilities::Direction::DOWN) {
        packet[1] = 3;
    } else 
    if (dir == Utilities::Direction::RIGHT) {
        packet[1] = 4;
    }
    return packet;
}

void Server::send(const char *data, int dataSize) {
    for (auto& addr : connections_) {
	socket_.send(addr, data, dataSize);
	// войти в стиль соколова и поставить тонну ассертов
    }
}

Client::Client(u16 serverPort, u16 myPort)
    : socket_(myPort)
    , server_(127, 0, 0, 1, serverPort)
{}

int Client::connect(const Address &addr) {
    assert(false);
}

void Client::receive(int dataMaxSize) {
    char packet[dataMaxSize];
    Address sender;
    if (socket_.receive(sender, packet)) {
        if (packet[0] == 0) { // init
	    // :(
        } else if (packet[0] == 1) { // pressed
	    if (InternetConnection::press) {
                if (packet[1] == 1) { // UP
                    InternetConnection::press(Utilities::Direction::UP);
                } else if (packet[1] == 2) { // LEFT 
                    InternetConnection::press(Utilities::Direction::LEFT);
                } else if (packet[1] == 3) { // DOWN 
                    InternetConnection::press(Utilities::Direction::DOWN);
                } else if (packet[1] == 4) { // RIGHT 
                    InternetConnection::press(Utilities::Direction::RIGHT);
                }
	    }
	} else if (packet[0] == 2) { // released
	    if (InternetConnection::release) {
                if (packet[1] == 1) { // UP
                    InternetConnection::release(Utilities::Direction::UP);
                } else if (packet[1] == 2) { // LEFT 
                    InternetConnection::release(Utilities::Direction::LEFT);
                } else if (packet[1] == 3) { // DOWN 
                    InternetConnection::release(Utilities::Direction::DOWN);
                } else if (packet[1] == 4) { // RIGHT 
                    InternetConnection::release(Utilities::Direction::RIGHT);
	        }
	    }
	}
    } else {
        // ну, по факту тут ниче делать не надо будет
    }
}

void Client::send(const char *data, int dataSize) {
    socket_.send(server_, data, dataSize);
}
