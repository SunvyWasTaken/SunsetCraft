//
// Created by sunvy on 17/02/2026.
//

#include "TcpTransport.h"

#include <arpa/inet.h>

namespace SunsetEngine
{
    TcpTransport::TcpTransport(SunsetEngine::ThreadSafeQueue<NetworkEvent>& queue)
        : m_Socket(-1)
        , m_Connected(false)
        , m_Queue(queue)
    {
    }

    TcpTransport::~TcpTransport()
    {
        Disconnect();
    }

    void TcpTransport::Connect(const std::string_view& host, uint16_t port)
    {
        m_Thread = std::thread([this, host, port]()
        {
            m_Socket = ::socket(AF_INET, SOCK_STREAM, 0);
            sockaddr_in serverAddr{};
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_port = htons(port);
            inet_pton(AF_INET, host.data(), &serverAddr.sin_addr);

            if (::connect(m_Socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
            {
                LOG("Engine", error, "Connection failed");
                return;
            }

            m_Connected = true;
            NetworkEvent ev{NetworkEvent::Type::Connected, {}};
            m_Queue.Push(ev);

            Poll();
        });
    }

    void TcpTransport::Send(const std::vector<uint8_t>& data)
    {
        ::send(m_Socket, data.data(), data.size(), 0);
    }

    void TcpTransport::Poll()
    {
        while (m_Connected)
        {
            uint8_t buffer[1024];
            if (const int bytes = recv(m_Socket, buffer, sizeof(buffer), 0); bytes > 0)
            {
                const NetworkEvent ev{NetworkEvent::Type::Message, std::vector<uint8_t>(buffer, buffer + bytes)};
                m_Queue.Push(ev);
            }
        }
    }

    void TcpTransport::Disconnect()
    {
        m_Connected = false;
        if (m_Thread.joinable())
            m_Thread.join();
        if (m_Socket >= 0)
            ::close(m_Socket);
    }
}
