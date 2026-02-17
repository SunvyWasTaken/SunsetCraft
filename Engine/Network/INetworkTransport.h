//
// Created by sunvy on 17/02/2026.
//

#ifndef SUNSETCRAFT_INETWORKTRANSPORT_H
#define SUNSETCRAFT_INETWORKTRANSPORT_H

struct NetworkEvent
{
    enum class Type { Connected, Disconnected, Message };
    Type type;
    std::vector<uint8_t> payload;
};

struct INetworkTransport
{
    virtual ~INetworkTransport() = default;
    virtual void Connect(const std::string_view& host, uint16_t port) = 0;
    virtual void Send(const std::vector<uint8_t>& data) = 0;
    virtual void Poll() = 0;
};

#endif //SUNSETCRAFT_INETWORKTRANSPORT_H